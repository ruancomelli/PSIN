% %% generate2dDEMGraph
% 
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Configuration:
inputPath = '../../_output/';    % Path where to look for input
nParticles = 2;             % Number of particles
timeJump = 10;
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

inputCell = cell(nParticles,1);

for k = 1 : nParticles
    files(k, :) = [inputPath, 'output', int2str(k), '.txt']; % Input files
    inputCell{k} = csvread(files(k, :));                % Data storage
end



% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
radius1 = 1;    % This should be automated
radius2 = .5;

% Get some data related to the simulation
inputMatrix = inputCell{1};

numberOfDerivatives = find( inputMatrix(:,1), 1, 'first' ) - 2;
timeStep = inputMatrix( 2 + numberOfDerivatives, 1 );

nTimeSteps = size(inputMatrix, 1) / (numberOfDerivatives + 1);

nDimensions = size(inputMatrix, 2) - 1;


% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%




%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%% NEW METHOD %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Configuration:
% inputPath = '../../_output/';    % Path where to look for input
% mainFile = fopen([inputPath, 'output.txt'], 'r');
% 
% nParticles = textscan(mainFile, 'Number of Particles = %d');             % Number of particles
% 
% initialTime = textscan(mainFile, 'Initial Time Instant = %f');
% timeStep = textscan(mainFile, 'Time Step = %f');
% finalTime = textscan(mainFile, 'Final Time Instant = %f'); 
% 
% timeJump = 10;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% inputCell = cell(nParticles,1);
% 
% for k = 1 : nParticles
%     files(k, :) = [inputPath, 'output', int2str(k), '.txt']; % Input files
%     inputCell{k} = csvread(files(k, :));                % Data storage
% end



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% radius1 = 1;    % This should be automated
% radius2 = .5;
% 
% % Get some data related to the simulation
% inputMatrix = inputCell{1};
% 
% numberOfDerivatives = find( inputMatrix(:,1), 1, 'first' ) - 2;
% timeStep = inputMatrix( 2 + numberOfDerivatives, 1 );
% 
% nTimeSteps = size(inputMatrix, 1) / (numberOfDerivatives + 1);
% 
% nDimensions = size(inputMatrix, 2) - 1;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%




%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
outputPath = '../../_output/';
video = VideoWriter([outputPath, 'outputVideo.avi']);
figure('Visible', 'off');
open(video)
F(nTimeSteps) = struct('cdata',[],'colormap',[]);
for j = 1:timeJump:nTimeSteps
    title([num2str(inputCell{1}((j-1)*(nDimensions+1) + 1, 1)), 's']);
    viscircles([inputCell{1}((j-1)*(nDimensions+1) + 2, 2), inputCell{1}((j-1)*(nDimensions+1) + 2, 3); inputCell{2}((j-1)*(nDimensions+1) + 2, 2), inputCell{2}((j-1)*(nDimensions+1) + 2, 3)], [radius1; radius2]);
    hold off
    axis([-15, 15, -15, 15]);
    F(j) = getframe(gcf);
    writeVideo(video, F(j));
end
close(video);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

