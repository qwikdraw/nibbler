## Nibbler - Swapable graphics plugin snake clone

This project focuses on implementing simple plugin system in c++  
using dynamic libraries. 

These plugins are used to provide differant rendering  
and input interfaces to a game of snake.

### Plugins
Each Plugin implements the following interface: 

```c++

struct Input
{
	bool	left;
	bool	right;
	bool	up;
	bool	down;
	bool	close;
	bool	one;
	bool	two;
	bool	three;
};

class IGraphic
{
protected:
	IGraphic(void) {}
	
public:
	virtual ~IGraphic(void) {};
	virtual void Draw(glm::ivec2, char) = 0;
	virtual void Display(void) = 0;
	virtual Input Input(void) = 0;
	virtual void Destroy(void) = 0;
};
```
Each dynamic library provides an extern function like so:
```c++
extern "C" IGraphic* load(glm::ivec2 dimensions) 
{
	return (new <Graphic>(glm::ivec2 dimensions));
}
```
where `<Graphic>` is the name of the `IGraphic` implementing class.


They are dynamically loaded through `dlopen` and `dlsym`  
and can be switched live with the `1`, `2`, and `3` keys.


### Dependencies
`glfw3 opengl glm sfml` 
On osx the *deps.sh* script will  
install all dependencies with 
brew.

### Building
`make nibbler` 

### Authors
 - Theo Walton
 - Logan Kaser
