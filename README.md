# UrbanMotion
AbstractProgrammingProject

Techniques:
- [ ] abstract classes and interfaces
- [ ] polymorphism
- [ ] templates and generic programming
- [ ] template metaprogramming - TMP
- [ ] concepts and constraints
- [ ] compile-time computations
- [ ] static polymorphism - CRTP
- [ ] type traits and SFINAE

## how to run locally
1. `mkdir build`
2. `cd build`
3. copy `map1.txt` to `build` dir
4. `cmake ..`
5. `cmake --build .`
6. `./UrbanMotion`


## chart
```mermaid
classDiagram
    class App {
        - int grid_size
        - int square_size
        - Window* appWindow
        - ImguiManager* imguiManager
        - Map* map
        - Panel* panel
        - bool is_initialized
        - MapFile* mapfile
        - TextureManager* textureManager
        + App(int grid_size, int square_size)
        + ~App()
        + bool init()
        + void run()
        + void shutdown()
    }

    class Window {
        + bool init()
        + int width
        + int height
        + void* getWindow()
        + void renderFrame()
    }

    class ImguiManager {
        + bool init()
        + bool shouldClose()
        + void beginFrame()
        + void endFrame()
    }

    class Panel {
        + Panel(int width, int height, int y_offset)
        + void setTextureRange(int max_texture_id)
        + void draw(void(*saveCallback)())
    }

    class TextureManager {
        + std::map<TextureID, int> loadTextures()
    }

    class MapFile {
        + MapFile(string fileName)
        + void saveMap()
    }

    class Map {
        + Map(int grid_width, int grid_height, int square_size, MapFile* mapfile, std::map<TextureID, int> textureMap)
        + void draw(Draw* draw_context)
        + void showChangeTilePanel(Draw* draw_context, int gridX, int gridY, Field* field)
    }

    class RotationTransform {
        + RotationTransform(const ImVec2& center, const ImVec2& size, int rotationDegrees)
        + std::array<ImVec2, 4> getTransformedVertices() const
        - ImVec2 center
        - glm::vec2 halfSize
        - int rotationDegrees
        - glm::mat2 rotationMatrix
    }

    class Field {
        + int textureId
        + bool isObstacle
    }

    App --> Window : appWindow
    App --> ImguiManager : imguiManager
    App --> Panel : panel
    App --> MapFile : mapfile
    App --> Map : map
    App --> TextureManager : textureManager
    Map --> RotationTransform : uses
    Map --> Field : contains
    App o-- ImGui : "uses ImGui functions"
```