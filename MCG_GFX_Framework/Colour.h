#ifndef COLOUR_H
#define COLOUR_H

// Framework includes.
#include <glm.hpp>

// Typedef includes.
#include <stdint.h>
#include <cmath>

/// <summary> Represents a 24-bit colour. </summary>
struct Colour
{
	/// <summary> Creates a black colour. </summary>
	Colour() : r(0), g(0), b(0) {}

	/// <summary> Creates a colour with the given values. </summary>
	/// <param name="_r"> The red. </param>
	/// <param name="_g"> The green. </param>
	/// <param name="_b"> The blue. </param>
	Colour(uint8_t _r, uint8_t _g, uint8_t _b) : r(_r), g(_g), b(_b) {}

	/// <summary> The red value between <c>0</c> and <c>255</c>. </summary>
	uint8_t r;

	/// <summary> The green value between <c>0</c> and <c>255</c>. </summary>
	uint8_t g;

	/// <summary> The blue value between <c>0</c> and <c>255</c>. </summary>
	uint8_t b;

	/// <summary> Calculates and returns this colour as a vector 3 where each value is between <c>0</c> and <c>1</c>. </summary>
	/// <returns> The calculated scalar vector. </returns>
	inline glm::vec3 ToScalar() const { return glm::vec3(r / (float_t)CHAR_MAX, g / (float_t)CHAR_MAX, b / (float_t)CHAR_MAX); }

	/// <summary> Blends these colours together using multiplication. </summary>
	/// <param name="_other"> The other colour with which to blend. </param>
	/// <returns> The blended colour. </returns>
	inline Colour operator*(const Colour& _other) const { return FromScalar(ToScalar() * _other.ToScalar()); }

	/// <summary> Blends this colour with the given scalar value using multiplication. </summary>
	/// <param name="_scalar"> The scalar with which to multiply. </param>
	/// <returns> The blended colour. </returns>
	inline Colour operator*(const float_t& _scalar) const { return FromScalar(ToScalar() * _scalar); }

	/// <summary> Blends these colours together using addition. </summary>
	/// <param name="_other"> The other colour with which to blend. </param>
	/// <returns> The blended colour. </returns>
	inline Colour operator+(const Colour& _other) const { return FromScalar(ToScalar() + _other.ToScalar()); }

	/// <summary> Blends this colour with the given scalar value using addition. </summary>
	/// <param name="_scalar"> The scalar with which to add. </param>
	/// <returns> The blended colour. </returns>
	inline Colour operator+(const float_t& _scalar) const { return FromScalar(ToScalar() + _scalar); }

	/// <summary> Implicitly converts this colour into a vector3. </summary>
	/// <returns> The converted colour. </returns>
	inline operator glm::ivec3() const { return glm::ivec3(r, g, b); }

	/// <summary> Creates a colour from the given scalar vector. </summary>
	/// <param name="_scalar"> The vector whose values are all between <c>0</c> and <c>1</c>. </param>
	/// <returns> The parsed colour. </returns>
	inline static Colour FromScalar(const glm::vec3 _scalar) { return Colour(glm::min((float_t)CHAR_MAX, ceil(_scalar.x * CHAR_MAX)), glm::min((float_t)CHAR_MAX, ceil(_scalar.y * CHAR_MAX)), glm::min((float_t)CHAR_MAX, ceil(_scalar.z * CHAR_MAX))); }

	/// <summary> Black. </summary>
	/// <returns> r0 b0 g0. </returns>
	inline static Colour Black() { return Colour(0, 0, 0); }

	/// <summary> White. </summary>
	/// <returns> r255 g255 b255. </returns>
	inline static Colour White() { return Colour(255, 255, 255); }

	/// <summary> Grey. </summary>
	/// <returns> r127 g127 b127. </returns>
	inline static Colour Grey() { return Colour(127, 127, 127); }

	/// <summary> Red. </summary>
	/// <returns> r255 b0 g0. </returns>
	inline static Colour Red() { return Colour(255, 0, 0); }

	/// <summary> Green. </summary>
	/// <returns> r0 b255 g0. </returns>
	inline static Colour Green() { return Colour(0, 255, 0); }

	/// <summary> Blue. </summary>
	/// <returns> r0 b0 g255. </returns>
	inline static Colour Blue() { return Colour(0, 0, 255); }
};
#endif