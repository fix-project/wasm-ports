(module
  (import "wasm2c" "memory" (memory $program_mem 0))
  (memory $ccontent (export "rw_mem_0") 1)
  (memory $cheader (export "rw_mem_1") 1)
  (memory $composer (export "rw_mem_2") 1)
  (memory $wasmcontent (export "ro_mem_0") 0)
  (table $input (export "ro_table_0") 0 externref)
  (table $return (export "rw_table_0") 3 externref)
  ;; rw_0
  (func (export "program_memory_to_rw_0") (param $offset i32) (param $ptr i32) (param $len i32)
    (memory.copy $program_mem $ccontent
    (local.get $offset)
    (local.get $ptr)
    (local.get $len))
  )
  ;; rw_1
  (func (export "program_memory_to_rw_1") (param $offset i32) (param $ptr i32) (param $len i32)
    (memory.copy $program_mem $cheader
    (local.get $offset)
    (local.get $ptr)
    (local.get $len))
  )
  ;; rw_2
  (func (export "program_memory_to_rw_2") (param $offset i32) (param $ptr i32) (param $len i32)
    (memory.copy $program_mem $composer
    (local.get $offset)
    (local.get $ptr)
    (local.get $len))
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
  ;; rw_table_0
  (func (export "set_rw_table_0") (param $index i32) (param $val externref) 
    (table.set $return (local.get $index) (local.get $val))
  )
)
