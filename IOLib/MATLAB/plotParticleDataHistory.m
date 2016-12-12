function plotParticleDataHistory( timeVector, particleData, index, dataName, outputMATLAB, fileName, ...
    xAxisLabel, yAxisLabel, colorMap, nParticles, component )
%plotParticleDataHistory

total = zeros(length(timeVector), 1);

for counter = 1 : nParticles
    total = total + particleData{counter, index}(:, component);
end

fig = figure('Visible', 'off');
    title(dataName);
    xlabel(xAxisLabel);
    ylabel(yAxisLabel);
    
    hold on
    
    for counter = 1 : nParticles
        plot(timeVector, particleData{counter, index}(:, component), ...
            'DisplayName', ['Particle ', int2str(counter)], ...
            'Color', colorMap(counter, :));
    end
    plot(timeVector, total, 'Color', 'black', ...
        'LineStyle', '-', ...
        'LineWidth', 1.0, ...
        'DisplayName', ['Total ', dataName]);
    legend('show', 'Location','southeast');
    
    saveas(fig, [outputMATLAB, fileName]);    
    hold off  

end

