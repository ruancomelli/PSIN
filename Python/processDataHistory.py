# -*- coding: utf-8 -*-
"""
@author: ruancomelli
@email: ruancomelli@sinmec.ufsc.br
"""

import numpy
import matplotlib.pyplot as plt


# FUNCTION
def plotParticleDataHistory( timeVector, particleData, index, dataName, outputMATLAB, fileName,
    extension, xAxisLabel, yAxisLabel, colorMap, nParticles, component ):

	total = numpy.zeros( len(timeVector) );

	for counter in range nParticles:
		total += particleData[counter][index][:][component]

	
	
	
	
	
# TEST
timeVector = [1, 2, 3]

nParticles = 2
index = 2
component = 1



print( plotParticleDataHistory([1,2,3], particleData=0, index=0, dataName=0, outputMATLAB=0, fileName=0,
    extension=0, xAxisLabel=0, yAxisLabel=0, colorMap=0, nParticles=0, component=0) )
	


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

