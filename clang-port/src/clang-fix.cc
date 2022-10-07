#include <clang/Basic/FileManager.h>
#include <clang/Basic/TargetInfo.h>
#include <clang/CodeGen/BackendUtil.h>
#include <clang/CodeGen/CodeGenAction.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendAction.h>
#include <clang/Frontend/TextDiagnosticPrinter.h>
#include <llvm/ADT/SmallVector.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/VirtualFileSystem.h>

#include "depfile.h"
#include "cc1args.h"
#include "wasm-rt-content.h"

using namespace std;

typedef char __attribute__( ( address_space( 10 ) ) ) * externref;
externref fixpoint_apply( externref encode ) __attribute__( ( export_name( "_fixpoint_apply" ) ) );

extern void program_memory_to_rw_0( int32_t, const void*, int32_t ) __attribute__( ( import_module( "asm" ), import_name( "program_memory_to_rw_0" ) ) );
extern void ro_0_to_program_memory( const void*, int32_t, int32_t ) __attribute__( ( import_module( "asm" ), import_name( "ro_0_to_program_memory" ) ) );
extern int32_t grow_rw_0( int32_t ) __attribute__( ( import_module( "asm" ), import_name( "grow_rw_0" ) ) );

extern void attach_blob_ro_mem_0( externref ) __attribute__( ( import_module( "fixpoint" ), import_name( "attach_blob_ro_mem_0" ) ) );
extern int32_t size_ro_mem_0( void ) __attribute__( ( import_module( "fixpoint" ), import_name( "size_ro_mem_0" ) ) );
extern externref create_blob_rw_mem_0( int32_t ) __attribute__( ( import_module( "fixpoint" ), import_name( "create_blob_rw_mem_0" ) ) );

extern externref get_ro_table_0( int32_t ) __attribute__( ( import_module( "asm" ), import_name( "get_ro_table_0" ) ) );
extern void attach_tree_ro_table_0( externref ) __attribute__( ( import_module( "fixpoint" ), import_name( "attach_tree_ro_table_0" ) ) );
extern externref get_ro_table_1( int32_t ) __attribute__( ( import_module( "asm" ), import_name( "get_ro_table_1" ) ) );
extern void attach_tree_ro_table_1( externref ) __attribute__( ( import_module( "fixpoint" ), import_name( "attach_tree_ro_table_1" ) ) );

using namespace clang;
using namespace llvm;

string c_to_elf( string_view depfile_views [], string_view sourcefile_views [] ) {
  llvm::InitializeAllTargets();
  llvm::InitializeAllTargetMCs();
  llvm::InitializeAllAsmPrinters();
  llvm::InitializeAllAsmParsers();

  // Create compiler instance
  clang::CompilerInstance compilerInstance;
  
  // Create diagnostic engine
  string diagOutput;
  raw_string_ostream diagOS( diagOutput );
  auto diagPrinter = make_unique<TextDiagnosticPrinter>( diagOS, new DiagnosticOptions() );

  IntrusiveRefCntPtr<DiagnosticsEngine> diagEngine
    = CompilerInstance::createDiagnostics( new DiagnosticOptions(), diagPrinter.get(), false );

  // Create File System
  IntrusiveRefCntPtr<vfs::InMemoryFileSystem> InMemFS( new vfs::InMemoryFileSystem() );
  
  for ( size_t i = 0; i < 147; i++ ) {
    InMemFS->addFile( clangdeps[i], 0, MemoryBuffer::getMemBuffer( depfile_views[i] ) );
  }

  InMemFS->addFile( "/fix/function.c", 0, MemoryBuffer::getMemBuffer( sourcefile_views[0] ) );
  InMemFS->addFile( "/fix/function.h", 0, MemoryBuffer::getMemBuffer( sourcefile_views[1] ) );
  InMemFS->addFile( "/fix/function_fixpoint.h", 0, MemoryBuffer::getMemBuffer( sourcefile_views[2] ) );
  InMemFS->addFile( "/fix/wasm-rt.h", 0, MemoryBuffer::getMemBuffer( wasm_rt_content ) );

  InMemFS->setCurrentWorkingDirectory("/fix");
  
  compilerInstance.setFileManager( new FileManager( FileSystemOptions {}, InMemFS ) );
  
  auto compilerInvocation = std::make_shared<CompilerInvocation>();
  if ( !CompilerInvocation::CreateFromArgs(*compilerInvocation, cc1args, *diagEngine) ) {
    return diagOS.str() + "\nFailed to create compiler invocation.\n"; 
  }
  
  LLVMContext context;
  std::unique_ptr<CodeGenAction> action( new EmitLLVMOnlyAction( &context ) );
  compilerInstance.createDiagnostics( diagPrinter.get(), false );
  compilerInstance.setInvocation( compilerInvocation );

  auto& codegenOptions = compilerInstance.getCodeGenOpts();
  codegenOptions.CodeModel = "large";
  codegenOptions.RelocationModel = llvm::Reloc::Static;

  if ( !compilerInstance.ExecuteAction( *action ) ) {
    return diagOS.str() + "\nFailed to emit llvm\n"; 
  }

  std::unique_ptr<llvm::Module> module = action->takeModule();
  if ( !module ) {
    return diagOS.str() + "\nFailed to take module\n";
  }

  std::string res;
  raw_string_ostream Str_OS( res );
  auto OS = make_unique<buffer_ostream>( Str_OS );

  EmitBackendOutput( compilerInstance.getDiagnostics(),
                     compilerInstance.getHeaderSearchOpts(),
                     compilerInstance.getCodeGenOpts(),
                     compilerInstance.getTargetOpts(),
                     compilerInstance.getLangOpts(),
                     compilerInstance.getTarget().getDataLayoutString(),
                     module.get(),
                     Backend_EmitObj,
                     std::move( OS ) );
  
  return res;
}

externref fixpoint_apply( externref encode ) {
  attach_tree_ro_table_0( encode );
  attach_tree_ro_table_1( get_ro_table_0( 2 ) );
  
  char* depfiles [146];
  string_view depfile_views[146];
  char* sourcefiles [3];
  string_view sourcefile_views[3];
  
  for ( size_t i = 0; i < 146; i++ ) {
    attach_blob_ro_mem_0( get_ro_table_1( i ) );
    char * buffer = (char*)malloc( size_ro_mem_0() );
    ro_0_to_program_memory( buffer, 0, size_ro_mem_0() );
    depfiles[i] = buffer;
    depfile_views[i] = string_view( depfiles[i], size_ro_mem_0() );
  }

  for ( size_t i = 3; i < 6; i++ ) {
    attach_blob_ro_mem_0( get_ro_table_0( i ) );
    char * buffer = (char*)malloc( size_ro_mem_0() );
    ro_0_to_program_memory( buffer, 0, size_ro_mem_0() );
    sourcefiles[i - 3] = buffer;
    sourcefile_views[i - 3] = string_view( sourcefiles[i - 3], size_ro_mem_0() );
  }
  
  string res = c_to_elf( depfile_views, sourcefile_views );
  
  if ( ( res.size() >> 12 ) > 0 ) {
    grow_rw_0( res.size() >> 12 );
  }
  program_memory_to_rw_0(0, res.data(), res.size());
  return create_blob_rw_mem_0( res.size() );
}
