%% generate2dDEMGraph

% Input:
path = '../../_output/';
nParticles = 2;

inputCell = cell(nParticles,1);

for k = 1 : nParticles
    files(k, :) = [path, 'output', int2str(k), '.txt'];
    inputCell{k} = csvread(files(k, :));
end

radius1 = 1;
radius2 = .5;

inputMatrix = inputCell{1};

numberOfDerivatives = find( inputMatrix(:,1), 1, 'first' ) - 2;
timeStep = inputMatrix( 2 + numberOfDerivatives, 1 );

nTimeSteps = size(inputMatrix, 1) / (numberOfDerivatives + 1);

nDimensions = size(inputMatrix, 2) - 1;

figure
F(nTimeSteps) = struct('cdata',[],'colormap',[]);
for j = 1:nTimeSteps
    title(num2str(inputCell{1}((j-1)*(nDimensions+1) + 1, 1)));
    viscircles([inputCell{1}((j-1)*(nDimensions+1) + 2, 2), inputCell{1}((j-1)*(nDimensions+1) + 2, 3); inputCell{2}((j-1)*(nDimensions+1) + 2, 2), inputCell{2}((j-1)*(nDimensions+1) + 2, 3)], [radius1; radius2]);
    hold off
    %plot(inputCell{1}((j-1)*(nDimensions+1) + 2, 2), inputCell{1}((j-1)*(nDimensions+1) + 2, 3),'b*' ,inputCell{2}((j-1)*(nDimensions+1) + 2, 2), inputCell{2}((j-1)*(nDimensions+1) + 2, 3), 'ro');
    axis([-15, 15, -15, 15]);
    F(j) = getframe(gcf);
end

figure
axes('Position',[0 0 1 1])
movie(F,1);