| **Control Flow** | **Function and Method** | **Class and Struct** |
|------------------|-------------------------|----------------------|
| break            | async                   | class                |
| case             | define                  | enum                 |
| continue         | fn                      | struct               |
| default          | inline                  | type                 |
| else             | macro                   | union                |
| for              | op                      |                      |
| if               | return                  |                      |
| match            | yield                   |                      |
| switch           |                         |                      |
| unless           |                         |                      |
| while            |                         |                      |

| **Inheritance and Polymorphism** | **Error Handling** | **Variable Declaration** |
|----------------------------------|--------------------|--------------------------|
| abstract                         | catch              | const                    |
| derives                          | finally            | let                      |
| interface                        | panic              | shared                   |
| requires                         | try                |                          |
|                                  | test               |                          |

| **Access Specifiers** | **Module Importing** | **Concurrency** | **Other** |
|-----------------------|----------------------|-----------------|-----------|
| mod                   | as                   | atomic          | delete    |
| priv                  | ffi                  | await           | is        |
| pub                   | import               | spawn           | null      |
| prot                  |                      | thread          | nullptr   |
| intl                  |                      |                 |           |

| **Complex Types** | **Signed Types** | **Unsigned Types** | **Data Types** | **Float Types** |
|-------------------|------------------|--------------------|----------------|-----------------|
| string            | i128             | u128               | int            | f32             |
| char              | i16              | u16                | float          | f64             |
| bool              | i32              | u32                | decimal        |                 |
| list              | i64              | u64                | void           |                 |
| map               | i8               | u8                 |                |                 |
| set               | isize            | usize              |                |                 |
| tuple             |                  |                    |                |                 |

| **Operators** |     |      |       |     |     |
|---------------|-----|------|-------|-----|-----|
| +             | /=  | ^=   | \|\|  | >>  | ::  |
| ++            | %   | ^^   | \|\|= | >>= | ->  |
| +=            | %=  | ^^=  | !     | ==  | =   |
| +-            | &   | ~    | !=    | === | **  |
| -             | &=  | ~&   | !&    | >   | **= |
| --            | &&  | ~&=  | !&=   | >=  |     |
| -=            | &&= | ~\|  | !\|   | <   |     |
| *             | @   | ~\|= | !\|=  | <=  |     |
| *=            | @=  | \|   | <<    | ..  |     |
| /             | ^   | \|=  | <<=   | ..= |     |

| **Feature** | **Class** | **Enum** | **Struct** | **Union** | **Interface** | **Abstract** |
|-------------|-----------|----------|------------|-----------|---------------|--------------|
| Default Visibility | (pub \| priv) by default | pub by default | Inverse of class default visibility | pub by default | Only pub visibility | (pub \| priv) by default |
| Methods Allowed | Methods allowed | Methods allowed (static only) | Methods allowed | No methods | Methods cannot contain implementations | Methods can contain implementations or have defaults |
| `self` \| `super` Param Allowed | `self` \| `super` params allowed | No `self` \| `super` params | `self` param allowed, `super` disallowed | Not applicable | `self` \| `super` params allowed | `self` \| `super` params allowed |
| Static Members Allowed | Static members allowed | Static members allowed | Static members allowed | Not applicable | Not applicable | Not applicable |
| Overhead | Larger overhead and vtable lookups (for derived) | Zero overhead | Minimal overhead | Minimal overhead | No vtable lookup | Large overhead (during compile) |
| Discriminants Allowed | Not applicable | Custom discriminants allowed | Not applicable | Tags allowed | Not applicable | Not applicable |
| Inheritance | Not mentioned | Not mentioned | No inheritance | Not mentioned | Any inherited object must implement all methods | Only methods without an implementation must be implemented; default implementations raise warnings if not implemented |
| Compile-Time Removal | Not applicable | Not applicable | Not applicable | Not applicable | Removed after compile | Removed after compile |
