#ifndef NORITER_SINGLETON_H
#define NORITER_SINGLETON_H

#include <utility>

namespace nrt {

/// Singleton template class
///
/// \note This singleton is not thread safe. For use of thread safe singleton,
/// use static initialization as:
///
/// // Singletone class Engine
/// class Engine : public Singleton<Engine> {};
///
/// // Call before main() and use theT only instead of calling getSingleton()
/// static T& theT = T::getSingleton();
template<class T>
class Singleton
{
public:
  /// Get reference of the singleton
  template <typename... Args>
  static T& getSingleton(Args... _args)
  {
    // http://stackoverflow.com/questions/1008019/c-singleton-design-pattern

    // Guaranteed to be destroyed and instantiated on first use.
    if (mInstance == nullptr)
    {
      static T instance(std::forward<Args>(_args)...);
      mInstance = &instance;
    }

    return *mInstance;
  }

  /// Get pointer of the singleton
  template <typename ... Args>
  static T* getSingletonPtr(Args... _args)
  {
    return &getSingleton(std::forward<Args>(_args)...);
  }

protected:
  /// Constructor
  Singleton() {}

  /// Destructor
  virtual ~Singleton() {}

private:
  /// Don't implement copy constructor
  Singleton(const T&) = delete;

  /// Don't assignment operator
  const T& operator=(const T&) = delete;

private:
  ///
  static T* mInstance;
};

/// Initialization of the singleton instance as nullptr pointer
template <class T> T* Singleton<T>::mInstance = nullptr;

}  // namespace nrt

#endif  // NORITER_SINGLETON_H
