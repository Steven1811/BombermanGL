#ifndef LIGHT_H
#define LIGHT_H
namespace Engine {
	class Light
	{
	private:
		float ambientStrength = 0.1f;

	public:
		Light();
		~Light();
	};
}
#endif