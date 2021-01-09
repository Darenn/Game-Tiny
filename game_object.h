#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject {
  public:
    int m_uniqueEngineID; // set by the engine when game object is created
    String name;
    String tag;
    virtual void update(unsigned long delta) {}
    virtual void awake() {}
    virtual void start() {}
    virtual void draw() {}
    virtual void onDestroy(){}

    virtual GameObject() {
      this->name = "none";
      this->tag = "none";
    }

    virtual GameObject(String name, String tag="default") {
      this->name = name;
      this->tag = tag;
    }

    bool operator==(const GameObject& other)
    {
        return m_uniqueEngineID == other.m_uniqueEngineID;
    }
};
#endif
