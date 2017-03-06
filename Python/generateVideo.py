from matplotlib import animation
from buildVideo import build_video

def generateVideo(timeVectorForPlot , scalarMap , pythonOutputFolder , simulationSettings , particleData , buildVideo , videoBools , videoTime):
	# Generate Video
	if( buildVideo ):
		print(">> Generating video")

		nParticles = simulationSettings["nParticles"]
		fileName = "CollidingSpheres"
		build_video(
			simulationSettings=simulationSettings,
			particleData=particleData,
			timeVector = timeVectorForPlot,
			scalarMap=scalarMap,
			outputFolder=pythonOutputFolder,
			fileName=fileName,
			videoBools=videoBools,
			videoTime=videoTime
			)

		print("<< Done")