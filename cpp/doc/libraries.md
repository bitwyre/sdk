# libraries

## unit testing

### catch2


### gtest

#### google mock

Mocks are objects that are pre-programmed to expect specific calls and
parameters and can throw exceptions when necessary.

**Example**
```cpp
Class MyMock : public MyInterface {
public:
  void SomeFunc(int param1){
     if(1!=param1)
	throw "I shouldn't be called!";}
}
```
Mock objects are the most intelligent test double. They are setup with expectation on how they will be called and will throw exception when those expectations are not met. (test double refers to any number of replacement objects that make testing easier. Test doubles stand in for software integration or features that are not easily testable. The test mock is one of the 5 main types of test doubles.)

##### Google Mock Workflow

* Create Mock classes derived from the interface classes that the mock is replacing

* In the Mock Class
