#include "GameObject.h"

#include "Transform.h"

GameObject::GameObject(){
    addComponent(new Transform());
}

template<typename T>
T* getComponent() {
    T* component = <T>(components[typeid(T)]);
    if (component == nullptr) std::cout << "Tried to get component " << typeid(T).name() << " but gameobject doesn't contain it" << std::endl;
    return component;
}

template<typename T>
void addComponent(const T* component) {
    components[typeid(T)] = component;
}