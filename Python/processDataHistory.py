# -*- coding: utf-8 -*-
"""
@author: ruancomelli
@email: ruancomelli@sinmec.ufsc.br
"""

import numpy
import matplotlib.pyplot as plt
from matplotlib import font_manager


# FUNCTION
def plotParticleDataHistory( timeVector, particleData, key, title, outputFolder, fileName,
    extension, xAxisLabel, yAxisLabel, scalarMap, nParticles, component = 0 ):

	if component == 'X':
		component = 0
	elif component == 'Y':
		component = 1
	elif component == 'Z':
		component = 2
		
	fig = plt.figure(
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
	
	# Set labels

	ax.set_xlabel(xAxisLabel, size=15, weight='normal', family='sans-serif')
	ax.set_ylabel(yAxisLabel, size=15, weight='normal', family='sans-serif')
	
	ax.set_title(title, size=25, weight='normal', family='sans-serif')
	
	# Set plot limits
	
	xMinimumLim = xMinimum - 0.1*xWidth
	xMaximumLim = xMaximum + 0.1*xWidth
	
	yMinimumLim = yMinimum - 0.1*yWidth
	yMaximumLim = yMaximum + 0.1*yWidth
	
	plt.xlim( xMinimumLim, xMaximumLim )
	plt.ylim( yMinimumLim, yMaximumLim )
	
	# Set plot ticks
	
	ax.tick_params(direction='both')
	ax.minorticks_on()
	
#	rangeStep = numpy.round(xWidth , int( numpy.abs(numpy.log10(xWidth)) + 1  ) )
#	xTicks = numpy.linspace(start=xMinimum , stop=xMaximum , num=10)
#	yTicks = numpy.linspace(start=yMinimum , stop=yMaximum , num=20)
#	
#	ax.set_xticks( xTicks )
#	ax.set_yticks( yTicks )

	# Add grid
	
	ax.grid(visible=True , which='major')
	ax.grid(visible=True , which='minor' , color=[0.5 , 0.5 , 0.5])
	
	ax.title.set_fontsize(25)
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
	
	
	handles, labels = ax.get_legend_handles_labels()
	handle_list, label_list = [], []
	for handle, label in zip(handles, labels):
	    if label not in label_list:
	        handle_list.append(handle)
	        label_list.append(label)
	
	lgd = ax.legend(handle_list, label_list, loc='right', prop={'size': 12, 'family': 'sans-serif', 'weight': 'normal'})
	lgd.set_title("Legend", prop={'size': 15, 'family': 'sans-serif', 'weight': 'normal'})
	
	plt.savefig(outputFolder + fileName + extension, bbox_inches = "tight")
	
	
	
	
	
def plotParticleDataHistory3D( timeVector, particleData, key, title, outputFolder, fileName,
	extension, xAxisLabel, yAxisLabel, scalarMap, nParticles ):

	plotParticleDataHistory( 
		timeVector = timeVector, 
		particleData = particleData, 
		key = key, 
		title = title + " - X Direction\n", 
		outputFolder = outputFolder, 
		fileName = fileName + "_X",
		extension = extension, 
		xAxisLabel = xAxisLabel, 
		yAxisLabel = yAxisLabel + " - X Direction", 
		scalarMap = scalarMap, 
		nParticles = nParticles, 
		component = 'X' )

	plotParticleDataHistory( 
		timeVector = timeVector, 
		particleData = particleData, 
		key = key, 
		title = title + " - Y Direction\n", 
		outputFolder = outputFolder, 
		fileName = fileName + "_Y",
		extension = extension, 
		xAxisLabel = xAxisLabel, 
		yAxisLabel = yAxisLabel + " - Y Direction", 
		scalarMap = scalarMap, 
		nParticles = nParticles, 
		component = 'Y' )

	plotParticleDataHistory( 
		timeVector = timeVector, 
		particleData = particleData, 
		key = key, 
		title = title + " - Z Direction\n", 
		outputFolder = outputFolder, 
		fileName = fileName + "_Z",
		extension = extension, 
		xAxisLabel = xAxisLabel, 
		yAxisLabel = yAxisLabel + " - Z Direction", 
		scalarMap = scalarMap, 
		nParticles = nParticles, 
		component = 'Z' )
	
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

