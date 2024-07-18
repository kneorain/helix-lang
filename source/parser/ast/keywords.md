| **N** | **Control Flow** | **Function and Method** | **Class and Struct** |
|-------|------------------|-------------------------|----------------------|
|   1   | break            | async                   | class                |
|   2   | case             | define                  | enum                 |
|   3   | continue         | fn                      | struct               |
|   4   | default          | inline                  | type                 |
|   5   | else             | macro                   | union                |
|   6   | for              | op                      |                      |
|   7   | if               | return                  |                      |
|   8   | match            | yield                   |                      |
|   9   | switch           |                         |                      |
|   10  | unless           |                         |                      |
|   11  | while            |                         |                      |
|   12  | in               |                         |                      |

| **N** | **Inheritance and Polymorphism** | **Error Handling** | **Variable Declaration** |
|-------|----------------------------------|--------------------|--------------------------|
|   1   | abstract                         | catch              | const                    |
|   2   | derives                          | finally            | let                      |
|   3   | interface                        | panic              | shared                   |
|   4   | requires                         | try                | final                    |
|   5   |                                  | test               |                          |

| **N** | **Access Specifiers** | **Module Importing** | **Concurrency** | **Other** |
|-------|-----------------------|----------------------|-----------------|-----------|
|   1   | module                | as                   | atomic          | delete    |
|   2   | private               | ffi                  | await           | is        |
|   3   | public                | import               | spawn           | null      |
|   4   | protected             |                      | thread          | nullptr   |
|   5   |                       |                      |                 | unsafe    |

| **N** | **Complex Types** | **Signed Types** | **Unsigned Types** | **Data Types** | **Float Types** |
|-------|-------------------|------------------|--------------------|----------------|-----------------|
|   1   | string            | i128             | u128               | int            | f32             |
|   2   | char              | i16              | u16                | float          | f64             |
|   3   | bool              | i32              | u32                | decimal        |                 |
|   4   | list              | i64              | u64                | void           |                 |
|   5   | map               | i8               | u8                 |                |                 |
|   6   | set               | isize            | usize              |                |                 |
|   7   | tuple             |                  |                    |                |                 |

| **N** | **Operators** |     |      |       |     |     |
|-------|---------------|-----|------|-------|-----|-----|
|   1   | +             | /=  | ^=   | \|\|  | >>  | ::  |
|   2   | ++            | %   | ^^   | \|\|= | >>= | ->  |
|   3   | +=            | %=  | ^^=  | !     | ==  | =   |
|   4   | +-            | &   | ~    | !=    | === | **  |
|   5   | -             | &=  | ~&   | !&    | >   | **= |
|   6   | --            | &&  | ~&=  | !&=   | >=  |     |
|   7   | -=            | &&= | ~\|  | !\|   | <   |     |
|   8   | *             | @   | ~\|= | !\|=  | <=  |     |
|   9   | *=            | @=  | \|   | <<    | ..  |     |
|   10  | /             | ^   | \|=  | <<=   | ..= |     |

|           **Feature**           |                     **Class**                    |            **Enum**           |             **Struct**                          |     **Union**    | **Interface** | **Abstract** |
|---------------------------------|--------------------------------------------------|-------------------------------|-------------------------------------------------|------------------|---------------|--------------|
| Default Visibility              | (pub \| priv) by default                         | pub by default                | Inverse of class default visibility             | pub by default   | Only pub visibility | (pub \| priv) by default |
| Methods Allowed                 | Methods allowed                                  | No Methods                    | Methods allowed                                 | No methods       | Methods cannot contain implementations | Methods can contain implementations or have defaults |
| `self` \| `super` Param Allowed | `self` \| `super` params allowed                 | No `self` \| `super` params   | `self` param allowed, `super` disallowed        | Not applicable   | `self` \| `super` params allowed | `self` \| `super` params allowed |
| Static Members Allowed          | Static members allowed                           | Static members allowed        | Static members allowed                          | Not applicable   | Not applicable | Not applicable |
| Overhead                        | Larger overhead and vtable lookups (for derived) | Zero overhead                 | Minimal overhead                                | Minimal overhead | No vtable lookup | Large overhead (during compile) |
| Discriminants Allowed           | Not applicable                                   | Custom discriminants allowed  | Not applicable                                  | Tags allowed     | Not applicable | Not applicable |
| Inheritance                     | Not mentioned                                    | Not mentioned                 | No inheritance                                  | Not mentioned    | Any inherited object must implement all methods | Only methods without an implementation must be implemented; default implementations raise warnings if not implemented |
| Compile-Time Removal            | Not applicable                                   | Not applicable                | Not applicable                                  | Not applicable   | Removed after compile | Removed after compile |
