(module
  (import "clang" "memory" (memory $program_mem 0))
  (memory $elfcontent (export "rw_mem_0") 1)
  (memory $wasmcontent (export "ro_mem_0") 0)
  (table $input (export "ro_table_0") 0 externref)
  (table $clang_deps (export "ro_table_1") 0 externref)
  ;; rw_0
  (func (export "program_memory_to_rw_0") (param $offset i32) (param $ptr i32) (param $len i32)
    (memory.copy $program_mem $elfcontent
    (local.get $offset)
    (local.get $ptr)
    (local.get $len))
  )
  (func (export "grow_rw_0") (param $size i32) (result i32)
    (memory.grow $elfcontent
    (local.get $size))
  )
  ;; ro_0
  (func (export "ro_0_to_program_memory") (param $offset i32) (param $ptr i32) (param $len i32)
    (memory.copy $wasmcontent $program_mem
    (local.get $offset)
    (local.get $ptr)
    (local.get $len))
  )
  ;; ro_table_0
  (func (export "get_ro_table_0") (param $index i32) (result externref)
    (table.get $input (local.get $index))
  )
  (func (export "size_ro_table_0") (result i32)
    (table.size $input)
  )
  ;; ro_table_1
  (func (export "get_ro_table_1") (param $index i32) (result externref)
    (table.get $clang_deps (local.get $index))
  )
  (func (export "size_ro_table_1") (result i32)
    (table.size $clang_deps)
  )
)
