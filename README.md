## Nibbler - Swapable graphics plugin snake clone

This project focuses on implementing simple plugin system in c++  
using dynamic libraries. 

These plugins are used to provide differant rendering  
and input interfaces to a game of snake.

### Plugins
Each Plugin implements the following interface: 

```c++
class IGraphic
{
public:
	IGraphic(glm::ivec2 grid_size);
	virtual ~IGraphic(void) = 0;
	virtual void Draw(glm::ivec2, char) = 0;
	virtual void Clear(void) = 0;
	virtual Input Input(void) = 0;
};
```
Each dynamic library must provides an extern function like so:
```c++
extern "C" IGraphic* load(void) 
{
	return (new <Graphic>());
}
```
where `<Graphic>` is the name of the `IGraphic` implementing class.


They are dynamically loaded through `dlopen` and `dlsym`  
and can be switched live with the `1`, `2`, and `3` keys.


### Dependencies
`glfw3 opengl glm sfml` 
On osx the deps.sh script will  
install all dependencies through  
brew.

### Building
`make nibbler` 

### Authors
 - Theo Walton
 - Logan Kaser
