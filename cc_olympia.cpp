#include <iostream>
#include <string>
#include <vector>

using namespace std;

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

class circle : public shape {
 public:
  void describe() {
    cout << "A circle has a radius." << endl;
    if (Dim_true) {
      Perimeter = 2 * 3.14 * Dims[0];
      Area = 3.14 * Dims[0] * Dims[0];

      cout << "Circumference of " << Name << " is " << Perimeter << endl;
      cout << "Area of " << Name << " is " << Area << endl;
    }
  }

  circle(string name, vector<float> dims) : shape(name) {
    if (dims.size() > 0) {
      if (dims.size() != 1 || dims[0] <= 0) {
        throw std::invalid_argument(
            "Circle requires exactly one positive radius");
      }
      Dim_true = true;
      Dims = dims;
    }
  }
};

class rectangle : public shape {
 public:
  void describe() {
    cout << "A rectangle has 4 sides broken into 2 side pairs of equal length "
            "and are parallel."
         << endl;
    if (Dim_true) {
      Perimeter = 2 * (Dims[0] + Dims[1]);
      Area = Dims[0] * Dims[1];

      cout << "Perimeter of " << Name << " is " << Perimeter << endl;
      cout << "Area of " << Name << " is " << Area << endl;
    }
  }

  rectangle(string name, vector<float> dims) : shape(name) {
    if (dims.size() > 0) {
      if (dims.size() != 2 || (dims[0] <= 0 || dims[1] <= 0)) {
        throw std::invalid_argument(
            "Rectangle requires exactly two positive sides");
      }
      Dim_true = true;
      Dims = dims;
    }
  }
};

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
        break;

      case ShapeName::SQUARE:
        return new square("Square", dims);
        break;

      case ShapeName::RECT:
        return new rectangle("Rectangle", dims);
        break;

      default:
        std::cerr << "Invalid shape name\n";
        break;
    }
  }
};

int main(int argc, char* argv[]) {
  int num_args = argc;
  string shape_name = argv[1];
  vector<float> dimensions;

  try {
    if (argc > 2) {
      for (int i = 2; i < argc; i++) {
        dimensions.push_back(std::stof(argv[i]));
      }
    }
  } catch (const std::exception& e) {
    std::cerr << "Invalid numeric input\n";
    return 1;
  }

  ShapeFactory* r = new ShapeFactory();
  shape* newShape = r->createShape(shape_name, dimensions);
  newShape->describe();

  return 0;
}