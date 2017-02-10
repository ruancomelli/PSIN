# -*- coding: utf-8 -*-
"""
@author: ruancomelli
@email: ruancomelli@sinmec.ufsc.br
"""

import numpy
import matplotlib
import matplotlib.pyplot as plt
from matplotlib import font_manager


# FUNCTION
def plotParticleDataHistory( timeVector, particleData, key, title, outputFolder, fileName,
    extension, xAxisLabel, yAxisLabel, scalarMap, nParticles, component = 0 ):
	
	fig = plt.figure( 
		num=1,
		figsize=(18, 14),
		facecolor='w',
		edgecolor='k' )

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
	
	# Set sizes and labels

	ax.set_xlabel(xAxisLabel, size=15, weight='normal', family='sans-serif')
	ax.set_ylabel(yAxisLabel, size=15, weight='normal', family='sans-serif')
	
	ax.set_title(title, size=25, weight='normal', family='sans-serif')
	plt.xlim( xMinimum - 0.1*xWidth, xMaximum + 0.1*xWidth )
	plt.ylim( yMinimum - 0.1*yWidth, yMaximum + 0.1*yWidth )
	
	#ax.title.set_fontsize(25)
	for label in (ax.get_xticklabels() + ax.get_yticklabels()):
	    label.set_fontproperties( font_manager.FontProperties(family='sans-serif', style='normal',
    size=15, weight='normal') )
					
	# Plot each particle key-property
	for counter in range(nParticles):
		ax.plot(
			timeVector, 
			particleData[counter][key][:, component],
			color = scalarMap.to_rgba(counter),
			label = "Particle " + str(counter)
			)

					
	# Plot total key-property
	ax.plot( 
		timeVector, 
		total,
		'k-',
		linewidth = 2.0,
		label = "Total"
		)
	
	lgd = ax.legend(loc='right', prop={'size': 12, 'family': 'sans-serif', 'weight': 'normal'})
	lgd.set_title("Legend", prop={'size': 15, 'family': 'sans-serif', 'weight': 'normal'})
		
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

