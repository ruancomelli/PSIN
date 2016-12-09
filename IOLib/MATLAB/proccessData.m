% %% proccessData.m
% 
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% %%%%%%%%%%%%%%%%%%%%%     INITIALIZE PROGRAM     %%%%%%%%%%%%%%%%%%%%%%%%%
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% inputPath:
clear
inputPath = '../../_output/';                   % Path where to look for input
outputMATLAB = '../../_output/MATLAB_output';   % Path where to MATLAB must output

% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% %%%%%%%%%%%%%%%%%%%%%%%%%%     READ DATA     %%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% ----- Read main output file -----
fileID = fopen([inputPath, 'output.txt']);
fileCell = textscan(fileID, '%s %f');

tags = fileCell{1};
values = fileCell{2};

% Number of Particles
nParticlesIdx = find( strcmpi(tags, '<nParticles>') );
nParticles = values(nParticlesIdx);

% Initial Instant
initialTimeStepIdx = find( strcmpi(tags, '<initialTime>') );
initialTime = values(initialTimeStepIdx);

% Time Step
timeStepIdx = find( strcmpi(tags, '<timeStep>') );
timeStep = values(timeStepIdx);

% Final Instant
finalTimeIdx = find( strcmpi(tags, '<finalTime>') );
finalTime = values(finalTimeIdx);

% Taylor Order
taylorOrderIdx = find( strcmpi(tags, '<taylorOrder>') );
taylorOrder = values(taylorOrderIdx);

% ----- Read particle files -----
energyIdx = 1;
positionIdx = 2;
velocityIdx = 2;
linearMomentumIdx = 2;
orientationIdx = 2;
rotationalVelocityIdx = 2;
angularMomentumIdx = 2;

numberOfFilesPerParticle = 7;
particleData = cell(nParticles, numberOfFilesPerParticle);


for counter = 1 : nParticles
    particleInputPath = [inputPath, 'Particle', int2str(counter), '/'];
    
    particleFileCell = textscan([particleInputPath, 'data.txt'], '%s %f');
    
    particleData{counter, energyIdx} = csvread([particleInputPath, 'energy.txt']);
    particleData{counter, positionIdx} = csvread([particleInputPath, 'position.txt']);
    particleData{counter, velocityIdx} = csvread([particleInputPath, 'velocity.txt']);
    particleData{counter, linearMomentumIdx} = csvread([particleInputPath, 'linear_momentum.txt']);
    particleData{counter, orientationIdx} = csvread([particleInputPath, 'orientation.txt']);
    particleData{counter, rotationalVelocityIdx} = csvread([particleInputPath, 'rotational_velocity.txt']);
    particleData{counter, angularMomentumIdx} = csvread([particleInputPath, 'angular_momentum.txt']);
end

% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% %%%%%%%%%%%%%%%%%%%%%%%%     PROCCESS DATA     %%%%%%%%%%%%%%%%%%%%%%%%%%%
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

nTimeSteps = (finalTime - initialTime) / timeStep + 1;
timeVector = initialTime:timeStep:finalTime;

% ----- Plot Energy -----
totalEnergy = zeros(nTimeSteps, 1);

for counter = 1 : nParticles
    totalEnergy = totalEnergy + particleData{counter, energyIdx};
end

fig = figure('Visible', 'off');
    title('Energy');
    xlabel('Time [s]');
    ylabel('Energy [J]');
    
    hold on
    
    
    for counter = 1 : nParticles
        plot(timeVector, particleData{counter, energyIdx});
        legend(['Particle ', int2str(counter)]);
    end
    plot(timeVector, totalEnergy, 'Color', 'black', 'LineStyle', '-', 'LineWidth', 1.0);
    
    saveas
    

% 
% nParticles = 2;
% 
% inputCell = cell(nParticles,1);
% 
% for k = 1 : nParticles
%     inputCell{k} = csvread([inputPath, 'Particle', int2str(k), '/position.txt']);                % Data storage
% end
% 
% 
% 
% % %%%%%%%%%%%%%%%%%%%%%%%%%% THIS IS WORKING!!! %%%%%%%%%%%%%%%%%%%%%%%%%%%
% radius(1) = 0.010;    % This should be automated
% radius(2) = 0.005;
% 
% % Get some data related to the simulation
% inputMatrix = inputCell{1};
% 
% initialTimes = find( inputMatrix(:,1), 2, 'first' );
% taylorOrder = initialTimes(2) - initialTimes(1) - 1 - 1;
% timeStep = inputMatrix(initialTimes(2),1) - inputMatrix(initialTimes(1),1);
% 
% finalTime = find( inputMatrix(:,1), 1, 'last' );
% nTimeSteps = floor( ( inputMatrix(finalTime,1) - inputMatrix(1,1) ) / timeStep + 1 );
% 
% nDimensions = size(inputMatrix, 2) - 1;
% 
% PositionCell = cell(nParticles, nTimeSteps);
% 
% % Get positions.
% % particleIdx: Index of the particle (1, 2, 3, ...)
% % timeIdx: Index of the time step (1 = initialTime, 2 =
% % initialTime + timeStep, 3 =
% % initialTime + 2*timeStep, ...)
% % derivativeIdx: (0 = position, 1 = velocity, 2 = acceleration, ...)
% % directionIdx: 1 = x, 2 = y, 3 = z;
% % Then we have PositionCell{particleIdx, timeIdx}(derivativeIdx+1,
% % directionIdx)
% for particleIdx = 1 : nParticles
%     for timeIdx = 1 : nTimeSteps
%         PositionCell{particleIdx, timeIdx}(taylorOrder + 1, nDimensions) = 0;
%         for derivativeIdx = 0 : taylorOrder
%             for directionIdx = 1 : 3
%                 PositionCell{particleIdx, timeIdx}(derivativeIdx + 1, directionIdx) = inputCell{particleIdx}( (timeIdx-1) * (taylorOrder+1 + 1) + (derivativeIdx+1) + 1, directionIdx + 1);
%             end
%         end
%     end
% end
% 
% disp('End of input section');
% % %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 
% %% VIDEO
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% timeJump = 100;
% 
% outputPath = '../../_output/';
% video = VideoWriter([outputPath, 'outputVideo.avi']);
% figure('Visible', 'off');
% open(video)
% 
% for i = 1 : nParticles
%     for j = 1 : nTimeSteps
%         xPos(i, j) = PositionCell{i,j}(1,1);
%         yPos(i, j) = PositionCell{i,j}(1,2);
%     end
%     xMin(i) = min(xPos(i,:));
%     xMax(i) = max(xPos(i,:));
%     yMin(i) = min(yPos(i,:));
%     yMax(i) = max(yPos(i,:));
% end
% 
% axis([min(xMin) - max(radius), max(xMax) + max(radius), min(yMin) - max(radius), max(yMax) + max(radius)]);
% axis equal
% 
% F(nTimeSteps) = struct('cdata',[],'colormap',[]);
% for j = 1:timeJump:nTimeSteps
%     title([num2str((j-1)*timeStep), 's']);
%     viscircles([inputCell{1}((j-1)*(nDimensions+1) + 2, 2), inputCell{1}((j-1)*(nDimensions+1) + 2, 3); inputCell{2}((j-1)*(nDimensions+1) + 2, 2), inputCell{2}((j-1)*(nDimensions+1) + 2, 3)], [0.010; 0.005]);
%     F(j) = getframe(gcf);
%     writeVideo(video, F(j));
% end
% close(video);
% 
% disp('End of video section');
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% %% PLOTTING
% %% position
% figure
% title('Speed');
% for i = 1 : nTimeSteps
%     xSpeed1(i) = PositionCell{1,i}(2, 1);
%     xSpeed2(i) = PositionCell{2,i}(2, 1);
% end
% plot( (0:(nTimeSteps-1))*timeStep, xSpeed1, 'b', (0:(nTimeSteps-1))*timeStep, xSpeed2, 'r')
% 
% disp('End of position plotting');
% 
% %% energy
% gravity = 10.0;
% figure
% title('Energy');
% 
% clear energy1
% clear energy2
% 
% mass1 = 0.001;
% mass2 = 0.0002;
% 
% for i = 1 : nTimeSteps
%     energy1(i) = mass1 * ( PositionCell{1,i}(2, 1)^2 + PositionCell{1,i}(2, 2)^2 + PositionCell{1,i}(2, 3)^2 )/2 + mass1 * norm(gravity) * PositionCell{1,i}(1,2);
%     energy2(i) = mass2 * ( PositionCell{2,i}(2, 1)^2 + PositionCell{2,i}(2, 2)^2 + PositionCell{2,i}(2, 3)^2 )/2 + mass2 * norm(gravity) * PositionCell{2,i}(1,2);
% end
% 
% plot((0:(nTimeSteps-1))*timeStep, energy1, 'b-', (0:(nTimeSteps-1))*timeStep, energy2, 'r-', (0:(nTimeSteps-1))*timeStep, energy1+energy2, 'k-');
% 
% disp('End of energy plotting');
% 
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%