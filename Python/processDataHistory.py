# -*- coding: utf-8 -*-
"""
@author: ruancomelli
@email: ruancomelli@sinmec.ufsc.br
"""

import numpy
import matplotlib.pyplot as plt


# FUNCTION
def plotParticleDataHistory( timeVector, particleData, key, title, outputFolder, fileName,
    extension, xAxisLabel, yAxisLabel, colorMap, nParticles, component = 0 ):

	#total = numpy.zeros( len(timeVector) )
	total = timeVector

	# for counter in range(nParticles):
	# 	total += particleData[counter][key][:, component]

	print(total)
	print(timeVector)

	plt.xlabel(xAxisLabel)
	plt.ylabel(yAxisLabel)
	plt.title(title)
	
	# for counter in range(nParticles):
	# 	plt.plot(
	# 		x = timeVector, 
	# 		y = particleData[counter][key][:, component]
	# 		)

	plt.plot( 
		xdata = timeVector, 
		ydata = total
		)
		
	# plt.plot(
	# 	x = timeVector,
	# 	y = total,
	# 	color = 'k',
	# 	linewidth = 2.0
	# 	)
	
	plt.show()
	plt.savefig(outputFolder + fileName + extension, bbox_inches = "tight")
	

	
	
	
	
	
def plotParticleDataHistory3D( timeVector, particleData, key, title, outputFolder, fileName,
    extension, xAxisLabel, yAxisLabel, colorMap, nParticles, component ):
	
	pass
	
# TEST	


#	for counter = 1 : nParticles
#	    total = total + particleData{counter, index}(:, component);
#	end
#	
#	fig = figure('Visible', 'off');
#	title(dataName);
#	xlabel(xAxisLabel);
#	ylabel(yAxisLabel);
#    
#	hold on
#    
#	for counter = 1 : nParticles
#		plot(timeVector, particleData{counter, index}(:, component),
#            'DisplayName', ['Particle ', int2str(counter-1)],
#            'Color', colorMap(counter, :));
#    
#    plot(timeVector, total, 'Color', 'black',
#        'LineStyle', '-',
#        'LineWidth', 1.0,
#        'DisplayName', ['Total ', dataName]);
#    legend('show', 'Location','southeast');
#    
#    saveas(fig, [outputMATLAB, fileName, extension]);    
#    hold off
#
#
#def plotParticleDataHistory3D( timeVector, particleData, index, dataName, outputMATLAB, fileName,
#    extension, xAxisLabel, yAxisLabel, colorMap, nParticles ):
#
#    plotParticleDataHistory( timeVector, particleData,
#        index, [dataName, ' - X Direction'], outputMATLAB, [fileName, '_X'],
#        extension, xAxisLabel, ['X ', yAxisLabel], colorMap,
#        nParticles, 1 );
#
#    plotParticleDataHistory( timeVector, particleData,
#        index, [dataName, ' - Y Direction'], outputMATLAB, [fileName, '_Y'],
#        extension, xAxisLabel, ['Y ', yAxisLabel], colorMap,
#        nParticles, 2 );
#
#    plotParticleDataHistory( timeVector, particleData,
#        index, [dataName, ' - Z Direction'], outputMATLAB, [fileName, '_Z'],
#        extension, xAxisLabel, ['Z ', yAxisLabel], colorMap,
#        nParticles, 3 );

