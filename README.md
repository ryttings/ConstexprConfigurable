# In search of a compile-time "configurable"

## Motivation

This is the quest to build a C++ structure that doesn't get in the way (of the kinds of problems I need to solve)

1. It feels silly to know that the information is *there*, but we can't access it.
    - Example 1:

        - Let's say I have a group of hardware registers that are part of some conceptual system. How would we write that in code? They're related, so an enum seems logical...
        ```cpp
        enum class RegisterId{
            SubsystemClock,
            SubsystemCtrl,
            SubsystemEnable
        };
        ```

        Now let's say that we want to do something similar for each register, but with different underlying implementations.
        ```cpp
        for (const auto reg : Registers){
            reg->write(values.at(reg.id)); //Write could be over PCI, SPI, some unified memory, etc...
        }
        ```

        This seems like a job for inheritance, though that costs a little.
        ```cpp
        struct RegisterBase{
            virtual void write() = 0;
        };

        struct Register : RegisterBase{};
        ```

        It also gets worse if we want to abstract more
        ```cpp
        struct RegisterBase{
            RegisterId id;
        };

        struct Register : RegisterBase{};

        struct SpiRegister : Register{};
        ...
        ```

        We also need to add the boilerplate of a getter/setter to anything in base structs, because the compiler can't figure out what we want when we inherit like this...
        ```cpp
        ```

        and... how do we do something like write "Do this for every SPI Register?"
        ```cpp
        //Something like this?
        struct SpiRegister : Register{
            SpiRegisterId id;
        };

        //But then we have to override our id() and setId()...

        ```cpp
        template <int I>
        struct Example{
        constexpr static auto value = I;
        int index = 3;
        };
        
        template <int I>
        struct Specialized : public Example<I> {
        };

        int main(){
            constexpr auto specialStruct = Specialized<1>;
            return specialStruct.value;
        }
        ```

        > Is CRTP an interesting option for something like this...?


