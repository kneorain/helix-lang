# casting - incomplete

a as unsafe int      // static_cast<int>(aa)
reinterpret a as int // reinterpret_cast<int>(aa)
eval a as int        // dynamic_cast<int>(a)
std::cast::reinterpret<>()

```cpp
namespace std {
    namespace cast {

        priv define create_cast(name: str) {
            define name(ty: Type!, val: Identifier! | Literal! ) {
                extern "C++" compiler::to_code!(f"{}_cast")<ty>(val);
            }
        }

        /** helix code:
        define static(ty: Type!, val: Val!) {
            extern "C++" static_cast<ty>(val);
        }
        */
        create_cast!("static");
        create_cast!("reinterpret");
        create_cast!("dynamic");
        create_cast!("const");
        create_cast!("volatile");


        macro any_cast(dest: Type!, src: Identifier! | Literal!) {
            return match (compiler::TARGET) {
                compiler::Target::CPP -> compiler::to_string!(unsafe extern "C++" (dest)src);
                compiler::Target::C   -> compiler::to_string!(extern "C" (dest)src);
                _                     -> panic MacroRuntimeError("Unsupported target");
            }
        }
    }
}


```
