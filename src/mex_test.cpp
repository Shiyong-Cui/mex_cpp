/**
 * A short tutorial how to write a MATLAB mex function using modern C++
 */

#include <string>
#include <memory>

#include "mex.hpp"
#include "mexAdapter.hpp"

using namespace matlab::mex;
using namespace matlab::data;

class MexFunction : public matlab::mex::Function {
public:
  void operator()(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs)
  {
    case5(outputs, inputs);
  }

private:

  // Structure Arrays: like this one of 1x5 struct array
  // friends(1).name = 'Jordan Robert';
  // friends(1).phone = 3386;
  // friends(2).name = 'Mary Smith';
  // friends(2).phone = 3912;
  // friends(3).name = 'Stacy Flora';
  // friends(3).phone = 3238;
  // friends(4).name = 'Harry Alpert';
  // friends(4).phone = 3077;
  void case6(matlab::mex::ArgumentList& outputs, matlab::mex::ArgumentList& inputs)
  {
    StructArray inStructArray = inputs[0];
    printDims(inStructArray);
    ArrayDimensions dims = inStructArray.getDimensions();
    size_t num_elements = inStructArray.getNumberOfElements();
    for (int i = 0; i < num_elements; ++i)
    {
      const Struct& entry = inStructArray[i];
      const CharArray& name = entry["name"];
      print(name);

      const double phone = entry["phone"][0];
      print(phone);
    }
  }

  // Structure: like st.Name = 'Color'; st.Value = ([1 0 1]);
  void case5(matlab::mex::ArgumentList& outputs, matlab::mex::ArgumentList& inputs)
  {
    const StructArray& inStruct = inputs[0];
    const Struct& entry = inStruct[0];
    const CharArray& name = entry["Name"];
    print(name);

    const TypedArray<double>& value = entry["Value"];
    print(value);
  }

  // Cell Arrays: {'MATLAB cell array', [1.2 2.2; 3.2 4.2]}
  void case4(matlab::mex::ArgumentList& outputs, matlab::mex::ArgumentList& inputs)
  {
    // suppose we have a cell array of 1x2 with values {'MATLAB cell array', [1.2 2.2; 3.2 4.2]}
    matlab::data::CellArray inCellArray = inputs[0];
    printDims(inCellArray);

    const CharArray& inCharArr = inCellArray[0];
    print(inCharArr);

    const TypedArray<double>& doubleArray = inCellArray[1];
    print(doubleArray);
  }

  // String Array: like ["Array", "of", "strings"] or "hello".
  void case3(matlab::mex::ArgumentList& outputs, matlab::mex::ArgumentList& inputs)
  {
    const TypedArray<MATLABString> stringArray = inputs[0];
    for (int i = 0; i < stringArray.getNumberOfElements(); ++i)
    {
      const std::string& str = std::string(stringArray[i]);
      stream << str.c_str() << std::endl;
      displayOnMATLAB(stream);
    }
  }

  // Character Array: like 'hello world'
  void case2(matlab::mex::ArgumentList& outputs, matlab::mex::ArgumentList& inputs)
  {
    const CharArray& inCharArr = inputs[0];
    print(inCharArr);
  }

  // Typed Arrays: a matrix of m x n
  void case1(matlab::mex::ArgumentList& outputs, matlab::mex::ArgumentList& inputs)
  {
    const TypedArray<double>& doubleArray = inputs[0];
    print(doubleArray);
  }

  template <typename T>
  void printDims(const TypedArray<T>& arr)
  {
    ArrayDimensions dims = arr.getDimensions();
    stream << "shape: (" << dims[0] << ", " << dims[1] << ")" << ", #elements: "
      << arr.getNumberOfElements() << std::endl;
    displayOnMATLAB(stream);
  }
  void print(const double val)
  {
    stream << val << std::endl;
    displayOnMATLAB(stream);
  }

  void print(const CharArray& inCharArr)
  {
    const std::string output_filename = inCharArr.toAscii();
    stream << output_filename.c_str() << std::endl;
    displayOnMATLAB(stream);
  }

  void print(const TypedArray<double>& doubleArray)
  {
    printDims(doubleArray);

    ArrayDimensions dims = doubleArray.getDimensions();
    for (int i = 0; i < dims[0]; ++i)
    {
      for (int j = 0; j < dims[1]; ++j)
      {
        double c = doubleArray[i][j];
        stream << c << " ";
        displayOnMATLAB(stream);
      }
      stream <<" \n ";
      displayOnMATLAB(stream);
    }
  }

  void displayOnMATLAB(std::ostringstream& stream)
  {
    // Pass stream content to MATLAB fprintf function
    matlabPtr->feval(u"fprintf", 0, std::vector<Array>({ factory.createScalar(stream.str()) }));
    // Clear stream buffer
    stream.str("");
  }

  // Pointer to MATLAB engine to call fprintf
  std::shared_ptr<matlab::engine::MATLABEngine> matlabPtr = getEngine();

  // Factory to create MATLAB data arrays
  ArrayFactory factory;

  // Create an output stream
  std::ostringstream stream;
};

