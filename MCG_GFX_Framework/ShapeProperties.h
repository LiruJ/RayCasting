#ifndef SHAPEPROPERTIES_H
#define SHAPEPROPERTIES_H

// Data includes.
#include "Colour.h"

// Typedef includes.
#include <cmath>

namespace Shapes
{
	/// <summary> Represents the properties that a shape may have. </summary>
	struct ShapeProperties
	{
		/// <summary> Creates a default property. </summary>
		ShapeProperties() : ShapeProperties(MatteGrey()) {}

		/// <summary> Creates a default property with the given colour. </summary>
		/// <param name="_colour"> The colour. </param>
		ShapeProperties(const Colour _colour) : ShapeProperties(MatteGrey()) { m_colour = _colour; }

		/// <summary> Creates a property with the given colour and reflectiveness. </summary>
		/// <param name="_colour"> The colour. </param>
		/// <param name="_reflectiveness"> The reflectiveness. </param>
		ShapeProperties(const Colour _colour, const float_t _reflectiveness) : m_colour(_colour), m_reflectiveness(_reflectiveness) { }

		/// <summary> The base colour. </summary>
		Colour m_colour;

		/// <summary> How reflective the object is. </summary>
		float_t m_reflectiveness;

		/// <summary> A non-reflective black. </summary>
		static ShapeProperties MatteBlack() { return ShapeProperties(Colour::Black(), 0); }

		/// <summary> A non-reflective grey. </summary>
		/// <remarks> Used as a default and base property. </remarks>
		static ShapeProperties MatteGrey() { return ShapeProperties(Colour::Grey(), 0); }

		/// <summary> Fully reflective. </summary>
		static ShapeProperties Shiny() { return ShapeProperties(Colour::White(), 1); }
	};
}
#endif