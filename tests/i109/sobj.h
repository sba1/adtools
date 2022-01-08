  #include <iostream>
  
  #define Q_DECL_EXPORT     __attribute__((visibility("default")))
  
  struct MetaObject {
      int i;
      char a;
  };
  
  template <typename...> struct List {};
  template <typename Head, typename... Tail> struct List<Head, Tail...> { typedef Head Car; typedef List<Tail...> Cdr; };
  
  template<typename Func> struct FunctionPointer { enum {ArgumentCount = -1, IsPointerToMemberFunction = false}; };
  template<class Obj, typename Ret, typename... Args> struct FunctionPointer<Ret (Obj::*) (Args...) const>
  {
      typedef Obj Object;
      typedef List<Args...>  Arguments;
      typedef Ret ReturnType;
      typedef Ret (Obj::*Function) (Args...) const;
      enum {ArgumentCount = sizeof...(Args), IsPointerToMemberFunction = true};
      // template <typename SignalArgs, typename R>
      // static void call(Function f, Obj *o, void **arg) {
      //     FunctorCall<typename Indexes<ArgumentCount>::Value, SignalArgs, R, Function>::call(f, o, arg);
      // }
  };
  
  class Q_DECL_EXPORT Object
  {
  public:
      static const MetaObject staticMetaObject;
      //Connect a signal to a pointer to qobject member function
    template <typename Func1>
      static inline MetaObject *connect(const Object *sender, Func1 signal)
      {
          typedef FunctionPointer<Func1> SignalType;
  
          // std::cout << "Before : " << SignalType::Object::staticMetaObject.i << " , " << SignalType::Object::staticMetaObject.a << "\n";
          std::cout << "Before : " << sender->staticMetaObject.i << " , " << sender->staticMetaObject.a << "\n";
          MetaObject *result = connectImpl(sender, reinterpret_cast<void **>(&signal),
                              &sender->staticMetaObject);
                              // &SignalType::Object::staticMetaObject);
          std::cout << "After : " << result->i << " , " << result->a << "\n";
  
          return result;
      }
  private:
      static MetaObject *connectImpl(const Object *sender, void **signal, const MetaObject *senderMetaObject);
  };
  