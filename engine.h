#ifndef ENGINE_H
#define ENGINE_H

#define MAX_GAMEOBJECT_COUNT 5

#include <Array.h>
#include "game_object.h"

class Engine {
  public:

    void start() {
      for(int i = 0; i < m_gameObjects.size(); i++) {
        auto go = m_gameObjects[i];
        go.start();
      } 
    }

    void awake() {
      for(int i = 0; i < m_gameObjects.size(); i++) {
        auto go = m_gameObjects[i];
        go.awake();
      } 
    }
    
    void update(unsigned long delta) {
      for(int i = 0; i < m_gameObjects.size(); i++) {
        auto go = m_gameObjects[i];
        go.update(delta);
      }
    }

    void draw() {
      for(int i = 0; i < m_gameObjects.size(); i++) {
        auto go = m_gameObjects[i];
        go.draw();
      }
    }

    void createGameObject(GameObject go) {
      m_gameObjects.push_back(go);
    }

    void destroyGameObject(GameObject& go) {
      for(int i = 0; i < m_gameObjects.size(); i++) {
        auto go = m_gameObjects[i];
        if(go == go) {
          go.onDestroy();
          m_gameObjects.remove(i);
        }
      }
    }

    private:
      Array<GameObject, MAX_GAMEOBJECT_COUNT> m_gameObjects;
};
#endif
