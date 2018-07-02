## Nibbler - Swapable graphics plugin snake clone

This project focuses on implementing simple plugin system in c++  
using dynamic libraries. 

These plugins are used to provide differant rendering  
and input interfaces to a game of snake.

### Plugins
Plugins implement the following interface: 

```
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
They are dynamically loaded through dlopen and dlsym  
and can be switched live. 


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
