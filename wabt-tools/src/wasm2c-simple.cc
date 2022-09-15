#include "src/apply-names.h"
#include "src/binary-reader-ir.h"
#include "src/binary-reader.h"
#include "src/error-formatter.h"
#include "src/feature.h"
#include "src/filenames.h"
#include "src/generate-names.h"
#include "src/ir.h"
#include "src/option-parser.h"
#include "src/stream.h"
#include "src/validator.h"
#include "src/wast-lexer.h"

#include "src/c-writer.h"

#include "wasminspector.hh"

using namespace wabt;
using namespace std;

typedef char __attribute__( ( address_space( 10 ) ) ) * externref;
externref fixpoint_apply( externref encode ) __attribute__( ( export_name( "_fixpoint_apply" ) ) );
extern void program_memory_to_rw_0( int32_t, const void*, int32_t ) __attribute__( ( import_module( "asm" ), import_name( "program_memory_to_rw_0" ) ) );
extern void program_memory_to_rw_1( int32_t, const void*, int32_t ) __attribute__( ( import_module( "asm" ), import_name( "program_memory_to_rw_1" ) ) );
extern void program_memory_to_rw_2( int32_t, const void*, int32_t ) __attribute__( ( import_module( "asm" ), import_name( "program_memory_to_rw_2" ) ) );
extern void ro_0_to_program_memory( const void*, int32_t, int32_t ) __attribute__( ( import_module( "asm" ), import_name( "ro_0_to_program_memory" ) ) );

extern void attach_blob_ro_mem_0( externref ) __attribute__( ( import_module( "fixpoint" ), import_name( "attach_blob_ro_mem_0" ) ) );
extern int32_t size_ro_mem_0( void ) __attribute__( ( import_module( "fixpoint" ), import_name( "size_ro_mem_0" ) ) );
extern externref create_blob_rw_mem_0( int32_t ) __attribute__( ( import_module( "fixpoint" ), import_name( "create_blob_rw_mem_0" ) ) );
extern externref create_blob_rw_mem_1( int32_t ) __attribute__( ( import_module( "fixpoint" ), import_name( "create_blob_rw_mem_1" ) ) );
extern externref create_blob_rw_mem_2( int32_t ) __attribute__( ( import_module( "fixpoint" ), import_name( "create_blob_rw_mem_2" ) ) );

extern externref get_ro_table_0( int32_t ) __attribute__( ( import_module( "asm" ), import_name( "get_ro_table_0" ) ) );
extern void attach_tree_ro_table_0( externref ) __attribute__( ( import_module( "fixpoint" ), import_name( "attach_tree_ro_table_0" ) ) );
extern void set_rw_table_0( int32_t, externref ) __attribute__( ( import_module( "asm" ), import_name( "set_rw_table_0" ) ) );
extern externref create_tree_rw_table_0( int32_t ) __attribute__( ( import_module( "fixpoint" ), import_name( "create_tree_rw_table_0" ) ) );

pair<MemoryStream&, MemoryStream&> wasm_to_c( string wasm_content ) __attribute__( ( export_name( "wasmtoc" ) ) ) {
  Errors errors;
  Module module;

  ReadBinaryOptions options;
  options.features.enable_multi_memory();
  options.features.enable_exceptions();
 
  ReadBinaryIr( "function", wasm_content.data(), wasm_content.size(), options, &errors, &module );
  ValidateModule( &module, &errors, options.features );
  GenerateNames( &module );
  ApplyNames( &module );
  
  wasminspector::WasmInspector inspector( &module, &errors );
  inspector.Validate();

  for ( auto index : inspector.GetExportedROMemIndex() ) {
   module.memories[index]->bounds_checked = true;
  }
  for ( auto index : inspector.GetExportedRWMemIndex() ) {
   module.memories[index]->bounds_checked = true;
  }
  
  WriteCOptions write_c_options;
  write_c_options.module_name = "function";
  MemoryStream c_stream;
  MemoryStream h_stream;
  WriteC( &c_stream, &h_stream, "function.h", &module, write_c_options );
  return { c_stream, h_stream };
}

externref fixpoint_apply( externref encode ) {
  attach_tree_ro_table_0( encode );
  attach_blob_ro_mem_0( get_ro_table_0( 0 ) );

  char* buffer = (char*)malloc( size_ro_mem_0() );
  ro_0_to_program_memory( buffer, 0, size_ro_mem_0() );
  string wasm_content( buffer, size_ro_mem_0() );

  auto result = wasm_to_c( wasm_content );
  auto c_output = result.first.ReleaseOutputBuffer();
  auto h_output = result.first.ReleaseOutputBuffer();
  
  program_memory_to_rw_0(0, &c_output->data, c_output->size());
  program_memory_to_rw_1(1, &h_output->data, h_output->size());
  externref c_blob = create_blob_rw_mem_0( c_output->size() );
  externref h_blob = create_blob_rw_mem_1( h_output->size() );
  
  free( buffer );

  set_rw_table_0( 0, c_blob );
  set_rw_table_0( 1, h_blob );
  return create_tree_rw_table_0( 3 );
}
