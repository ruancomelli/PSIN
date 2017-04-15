# Default values
simulationName	= "Simulation1"
buildType		= "Release"
programName		="CollidingSpheres.exe"

# options
buildTypes		= ["Release" , "Debug"]
videoTypes		= ["by_time_step" , "global" , "autoscale"]
plotTypes		= [ "energy" , "linear_momentum" , "angular_momentum" , "force" , "torque" ]

# All classes will receive a frame. That will be
# where they must show their widgets.
#
# Class Alpha( frame ):
#    ...
# --- end of class ---