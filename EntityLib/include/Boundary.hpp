// #ifndef BOUNDARY_H
// #define BOUNDARY_H

// // Standard
// #include <functional>

// // EntityLib
// #include <PhysicalEntity.hpp>

// // UtilsLib
// #include <SharedPointer.hpp>

// class Boundary: public PhysicalEntity
// {
// 	using BoundaryPtr = SharedPointer<Boundary>;
// 	using Spatial = vector<Vector3D>;

// 	public:
// 		void setPositionFunction( const std::function< Spatial(double)> & f );
// 		void setOrientationFunction( const std::function< Spatial(double)> & f );

// 		void updatePosition(double t);
// 		void updateOrientation(double t);
		
// 	private:
// 		std::function< Spatial(double)> positionFunction;
// 		std::function< Spatial(double)> orientationFunction;
// }; // class Boundary

// using BoundaryPtr = SharedPointer<Boundary>;

// #endif
