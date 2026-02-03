# Shape Factory  
**Factory Method Design Pattern – C++**

This project demonstrates core **Object-Oriented Programming (OOP)** concepts in C++—with a strong focus on the **Factory Method Design Pattern** and the **Open–Closed Principle (OCP)**.  
It provides a clean, extensible way to create and operate on different geometric shapes without modifying existing code.

---

## 🚀 Key OOP Concepts Demonstrated
- **Encapsulation** – Shape-specific logic is hidden within classes  
- **Abstraction** – Common behavior defined via a base class  
- **Polymorphism** – Runtime binding using virtual functions  
- **Factory Method Pattern** – Object creation delegated to a factory  
- **Open–Closed Principle (OCP)** – Extend functionality without modifying existing code  

---

## 🛠️ Build & Run

### Compile
```bash
g++ cc_olympia.cpp -o cc_olympia
```
Run
```bash
./cc_olympia <shape> <list of dimensions>
```
Supported Shapes

- circle

- square

- rect

Note: Dimensions are optional. If provided, they are validated strictly.

📌 Usage Examples
Rectangle
```bash
./cc_olympia rect 5 7
```

Output
```bash
A rectangle has 4 sides broken into 2 side pairs of equal length and are parallel.
Perimeter of Rectangle is 24
Area of Rectangle is 35
```

Square (No Dimensions)
```bash
./cc_olympia square
```

Output
```bash
A square has four sides that are of equal length.
```
---
## ❌ Invalid Input Handling
The program robustly handles invalid or inconsistent dimensions using exceptions.

Examples
```bash
./cc_olympia square -6

terminate called after throwing an instance of 'std::invalid_argument'
what(): Square requires exactly one positive side
```
```bash
./cc_olympia square 6 7

terminate called after throwing an instance of 'std::invalid_argument'
what(): Square requires exactly one positive side
```
```bash
./cc_olympia rect 5

terminate called after throwing an instance of 'std::invalid_argument'
what(): Rectangle requires exactly two positive sides
```
---
## 🧠 Code Overview
### 1️⃣ Base Class: shape
```bash
class shape {
 protected:
  float Perimeter;
  float Area;
  string Name;
  bool Dim_true = false;
  vector<float> Dims;

 public:
  virtual void describe() = 0;
  shape(string name) { Name = name; }
};
```
- Abstract base class for all shapes
- Stores common attributes
- Enforces implementation of describe() via a pure virtual function

### 2️⃣ Derived Class Example: square
```bash
class square : public shape {
 public:
  void describe() {
    cout << "A square has four sides that are of equal length." << endl;
    if (Dim_true) {
      Perimeter = 4 * Dims[0];
      Area = Dims[0] * Dims[0];
      cout << "Perimeter of " << Name << " is " << Perimeter << endl;
      cout << "Area of " << Name << " is " << Area << endl;
    }
  }

  square(string name, vector<float> dims) : shape(name) {
    if (dims.size() > 0) {
      if (dims.size() != 1 || dims[0] <= 0) {
        throw std::invalid_argument(
            "Square requires exactly one positive side");
      }
      Dim_true = true;
      Dims = dims;
    }
  }
};
```
- Validates dimensions at construction time
- Computes area and perimeter only when dimensions are available
- Encapsulates all shape-specific logic

### 3️⃣ Factory Class: ShapeFactory
```bash
class ShapeFactory {
 public:
  enum class ShapeName : uint8_t { CIRCLE, SQUARE, RECT, UNKNOWN };

  ShapeName getShapeEnum(const std::string& name) {
    if (name == "circle") return ShapeName::CIRCLE;
    if (name == "square") return ShapeName::SQUARE;
    if (name == "rect") return ShapeName::RECT;
    return ShapeName::UNKNOWN;
  }

  shape* createShape(string name, vector<float> dims) {
    ShapeName shape = getShapeEnum(name);

    switch (shape) {
      case ShapeName::CIRCLE:
        return new circle("Circle", dims);
      case ShapeName::SQUARE:
        return new square("Square", dims);
      case ShapeName::RECT:
        return new rectangle("Rectangle", dims);
      default:
        std::cerr << "Invalid shape name\n";
        return nullptr;
    }
  }
};
```
- Centralized object creation
- Decouples main() from concrete shape implementations
- Makes the system easily extensible

### 4️⃣ Main Function
```bash
int main(int argc, char* argv[]) {
  string shape_name = argv[1];
  vector<float> dimensions;

  try {
    for (int i = 2; i < argc; i++) {
      dimensions.push_back(std::stof(argv[i]));
    }
  } catch (...) {
    std::cerr << "Invalid numeric input\n";
    return 1;
  }

  ShapeFactory factory;
  shape* newShape = factory.createShape(shape_name, dimensions);
  newShape->describe();

  return 0;
}
```
- Parses command-line arguments
- Uses the factory to create shape objects
- Demonstrates runtime polymorphism
---
## 🌟 Design Highlights

- **Follows the Open–Closed Principle**
- **Clean separation of concerns**
- **Robust exception handling**
- **Easy to extend with new shapes**

## 🔧 Extending the Project

To add a new shape:
- **Create a new class inheriting from shape**
- **Implement the describe() method**
- **Register the shape in ShapeFactory**
- **No changes to main() are required**
