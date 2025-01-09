# UrbanMotion
AbstractProgrammingProject

Techniques:
- [x] abstract classes and interfaces
- [x] polymorphism
- [x] templates and generic programming
- [ ] template metaprogramming - TMP
- [ ] concepts and constraints
- [x] compile-time computations
- [ ] static polymorphism - CRTP
- [x] type traits and SFINAE

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
        + void renderFrame(bool mapInitialized)
        + void setMapInitializationCallback(std::function<void(const std::string&)> callback)
        + void setMapSaveCallback(std::function<void()> callback)
        + void setMap(Map* newMap)
        + void setDropTargetWindow(std::unique_ptr<DropTargetWindow> newDrop)
        + void setCounter(int value)
        + void shutdown()
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
        + void draw(void(*saveCallback)(), void(*screenshotCallback)(), Map* map)
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
        + int showChangeTilePanel(Draw* draw_context, int gridX, int gridY, Field* field, Texture::ID id)
        + int getSquareSize()
        + FieldMatrix getFieldMatrix()
        + bool checkingRoad(std::shared_ptr<Field> field)
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
        + void draw(Draw* context, const Point& min, const Point& max) const
        + Texture::ID getID()
        + void setVehicle(bool occupied, std::shared_ptr<Vehicle> vehicle)
        + bool hasVehicle() const
    }

    class Vehicle {
        + Vehicle(Texture::ID id, int selectedX, int selectedY, int rotationDegrees = 0)
        + void moveUp()
        + void moveDown()
        + void moveLeft()
        + void moveRight()
        + void setPosition(const Point& pos)
        + void setID(Texture::ID id)
        + Texture::ID getID() const
        + Point getPosition() const
        + int getX() const
        + int getY() const
        - Point position
        - Texture::ID textureID
        - int rotation
        - int x, y
    }

    class Car {
        + Car(int x, int y, int rotationDegrees = 0)
    }

    class ListOfVehicle {
        + void addVehicle(std::shared_ptr<Vehicle> vehicle)
        + void removeVehicle(int x, int y)
        + size_t size() const
        + void printAllVehicles() const
        + const std::vector<std::shared_ptr<Vehicle>>& get() const
        - std::vector<std::shared_ptr<Vehicle>> vehicles
    }

    App --> Window : appWindow
    App --> ImguiManager : imguiManager
    App --> Panel : panel
    App --> MapFile : mapfile
    App --> Map : map
    App --> TextureManager : textureManager
    Map --> RotationTransform : uses
    Map --> Field : contains
    Map --> ListOfVehicle : contains
    ListOfVehicle --> Vehicle : contains
    Vehicle <|-- Car
    App o-- ImGui : "uses ImGui functions"
```