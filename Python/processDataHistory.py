# -*- coding: utf-8 -*-
"""
@author: ruancomelli
@email: ruancomelli@sinmec.ufsc.br
"""

import numpy

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt


# FUNCTION
def plotParticleDataHistory( timeVector, particleData, key, title, outputFolder, fileName,
    extension, xAxisLabel, yAxisLabel, colorMap, nParticles, component = 0 ):
	
	fig = plt.figure()
	ax = fig.add_subplot(111)
	yMinimum = min(particleData[0][key][:, component])
	yMaximum = max(particleData[0][key][:, component])

	xMinimum = min(timeVector)
	xMaximum = max(timeVector)

	total = numpy.zeros( len(timeVector) )

	for counter in range(nParticles):
		total += particleData[counter][key][:, component]

		yMinimum = min( min(particleData[counter][key][:, component]), yMinimum )
		yMaximum = max( max(particleData[counter][key][:, component]), yMaximum )
		
	yMinimum = min( min(total), yMinimum )
	yMaximum = max( max(total), yMaximum )
	
	xWidth = xMaximum - xMinimum
	yWidth = yMaximum - yMinimum

	ax.set_xlabel(xAxisLabel)
	ax.set_ylabel(yAxisLabel)
	plt.title(title)
	plt.xlim( xMinimum - 0.1*xWidth, xMaximum + 0.1*xWidth )
	plt.ylim( yMinimum - 0.1*yWidth, yMaximum + 0.1*yWidth )
	
	for counter in range(nParticles):
		ax.plot(
			timeVector, 
			particleData[counter][key][:, component]
			)

	ax.plot( 
		timeVector, 
		total,
		'k-',
		linewidth = 2.0
		)
		
	# plt.plot(
	# 	x = timeVector,
	# 	y = total,
	# 	color = 'k',
	# 	linewidth = 2.0
	# 	)
	
	# plt.show()
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

