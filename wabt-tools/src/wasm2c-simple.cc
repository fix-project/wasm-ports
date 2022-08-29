#include <cinttypes>
#include <cstdlib>

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
// externref fixpoint_apply( externref encode ) __attribute__( ( export_name( "_fixpoint_apply" ) ) );

pair<MemoryStream&, MemoryStream&> wasm_to_c( string wasm_content ) {
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
