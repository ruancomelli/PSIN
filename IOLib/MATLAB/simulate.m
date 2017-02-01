function simulate( simulationName )
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% %%%%%%%%%%%%%%%%%%%%%     INITIALIZE SCRIPT     %%%%%%%%%%%%%%%%%%%%%%%%%
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

disp('> Initializing Program');

%% inputPath:

disp(['==== ', simulationName, ' ====']);

inputFileID = fopen('../../_input/input.txt', 'w');
fprintf(inputFileID, '%s', ['<simulationName> ', simulationName]);

inputPath = ['../../_output/', simulationName, '/'];                    % Path where to look for input
outputMATLAB = ['../../_output/', simulationName, '/MATLAB_output/'];   % Path where to MATLAB must output

disp('< Done');

% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% %%%%%%%%%%%%%%%%%%%%%%%     EXECUTE PROGRAM     %%%%%%%%%%%%%%%%%%%%%%%%%%
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

disp('> Simulating');

programPath = '../../_tests/';
programName = 'collidingspheres_x64.exe';

if isunix
    system(['cd ', programPath, ' ; ./', programName]);
elseif ispc
    system(['cd ', programPath, ' & ', programName]);
end

% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% %%%%%%%%%%%%%%%%%%%%%%%%%%     READ DATA     %%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% ----- Read main output file -----
disp('> Reading Main Output File');

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

% Time steps for output
timeStepsForOutputIdx = find( strcmpi(tags, '<timeStepsForOutput>') );
timeStepsForOutput = values(timeStepsForOutputIdx);

disp('< Done')

%% ----- Read particle files -----
disp('> Reading Particle Files');

energyIdx = 1;
positionIdx = 2;
velocityIdx = 3;
linearMomentumIdx = 4;
orientationIdx = 5;
rotationalVelocityIdx = 6;
angularMomentumIdx = 7;
forceIdx = 8;
torqueIdx = 9;

numberOfFilesPerParticle = 9;
particleData = cell(nParticles, numberOfFilesPerParticle);
particleFileCell = cell(nParticles, 1);

for counter = 1 : nParticles
    disp(['Particle ', int2str(counter-1)]);

    particleInputPath = [inputPath, 'Particle', int2str(counter-1), '/'];
    
    fileID = fopen([particleInputPath, 'data.txt']);
    particleFileCell{counter} = textscan(fileID, '%s %f');
    
    particleData{counter, energyIdx} = csvread([particleInputPath, 'energy.txt']);
    particleData{counter, positionIdx} = csvread([particleInputPath, 'position.txt']);
    particleData{counter, velocityIdx} = csvread([particleInputPath, 'velocity.txt']);
    particleData{counter, linearMomentumIdx} = csvread([particleInputPath, 'linear_momentum.txt']);
    particleData{counter, orientationIdx} = csvread([particleInputPath, 'orientation.txt']);
    particleData{counter, rotationalVelocityIdx} = csvread([particleInputPath, 'rotational_velocity.txt']);
    particleData{counter, angularMomentumIdx} = csvread([particleInputPath, 'angular_momentum.txt']);
    particleData{counter, forceIdx} = csvread([particleInputPath, 'force.txt']);
    particleData{counter, torqueIdx} = csvread([particleInputPath, 'torque.txt']);
end

timeVectorLength = length( particleData{1, energyIdx}(:, 1) );

disp('< Done');

% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% %%%%%%%%%%%%%%%%%%%%%%%%     PROCCESS DATA     %%%%%%%%%%%%%%%%%%%%%%%%%%%
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
disp('> Proccessing Data');

radius = zeros(nParticles, 1);
for counter = 1 : nParticles
    radiusIdx = find( strcmpi(particleFileCell{counter}{1},'<Radius>') );
    radius(counter) = particleFileCell{counter}{2}(radiusIdx);
end

timeVector = initialTime:(timeStepsForOutput*timeStep):(finalTime+timeStep);
timeVector = timeVector(1:length(particleData{1,energyIdx}(:,1)));
nTimeSteps = timeStepsForOutput * length(timeVector);

cmap = colormap( jet(nParticles) );
temp = cmap(2,:);
cmap(2, :) = [1.0, 0.0, 0.0]; % red
cmap(4,:) = temp;

%% ----- Plot Energy -----
disp('>> Plotting Energy');

plotParticleDataHistory(timeVector, particleData,...
    energyIdx, 'Mechanical Energy', ...
    outputMATLAB, 'mechanical_energy_plot', '.png', ...
    'Time [s]', 'Mechanical Energy [J]', ...
    cmap, nParticles, 1);

disp('<< Done');
    
%% ----- Plot Linear Momentum -----
disp('>> Plotting Linear Momentum');

plotParticleDataHistory3D( timeVector, particleData, ...
    linearMomentumIdx, 'Linear Momentum', ...
    outputMATLAB, 'linear_momentum_plot', '.png', ...
    'Time [s]', 'Linear Momentum [kg*m/s]', ...
    cmap, nParticles );
    
disp('<< Done');
    
    
%% ----- Plot Angular Momentum -----
disp('>> Plotting Angular Momentum');

plotParticleDataHistory3D( timeVector, particleData, ...
    angularMomentumIdx, 'Angular Momentum', ...
    outputMATLAB, 'angular_momentum_plot', '.png', ...
    'Time [s]', 'Angular Momentum [kg*m^2/s]', ...
    cmap, nParticles ); 

disp('<< Done');

%% ----- Plot Force -----
disp('>> Plotting Resulting Force');

plotParticleDataHistory3D( timeVector, particleData, ...
    forceIdx, 'Resulting Force', ...
    outputMATLAB, 'resulting_force_plot', '.png', ...
    'Time [s]', 'Resulting Force [N]', ...
    cmap, nParticles );

disp('<< Done');

%% ----- Plot Torque -----
disp('>> Plotting Resulting Torque');

plotParticleDataHistory3D( timeVector, particleData, ...
    torqueIdx, 'Resulting Torque', ...
    outputMATLAB, 'resulting_torque_plot', '.png', ...
    'Time [s]', 'Resulting Torque [N*m]', ...
    cmap, nParticles );

disp('<< Done');

disp('< Done');

%% ===== Generate Movie =====
boolGenerateMovie = true;

if boolGenerateMovie

    disp('> Generating Movie');

    timeSkip = 0;
    disp(['Skipping ', int2str(timeSkip), ' time steps per frame']);

    video = VideoWriter([outputMATLAB, 'outputVideo.avi']);

    figure('Visible', 'off');
    open(video)

    xPos = zeros(nParticles, timeVectorLength);
    yPos = zeros(nParticles, timeVectorLength);

    xMin = zeros(nParticles, 1);
    yMin = zeros(nParticles, 1);
    xMax = zeros(nParticles, 1);
    yMax = zeros(nParticles, 1);

    for i = 1 : nParticles
        for j = 1 : timeVectorLength
            xPos(i, j) = particleData{i,positionIdx}(j,1);
            yPos(i, j) = particleData{i,positionIdx}(j,2);
        end
        xMin(i) = min(xPos(i,:));
        xMax(i) = max(xPos(i,:));
        yMin(i) = min(yPos(i,:));
        yMax(i) = max(yPos(i,:));
    end

    axis([min(xMin) - max(radius), max(xMax) + max(radius), min(yMin) - max(radius), max(yMax) + max(radius)]);
    axis equal

    Frame(timeVectorLength) = struct('cdata',[],'colormap',[]);
    for j = 1 : (timeSkip+1) : timeVectorLength
        title([num2str(initialTime + (j-1)*timeStep*timeStepsForOutput), 's']);

        % Get center coordinates
        X = xPos(:, j);
        Y = yPos(:, j);
        centers = [X, Y];

        % Clear circles drawn before
        cla

        axis([min(xMin) - 2*max(radius), max(xMax) + 2*max(radius), min(yMin) - 2*max(radius), max(yMax) + 2*max(radius)]);
        axis equal
        set(gca,'Color',[0.8 0.8 0.8]);

        % Plot circles
        for counter = 1 : nParticles
            viscircles(centers(counter, :), radius(counter), 'EdgeColor', cmap(counter, :));
        end

        % Write to video
        Frame(j) = getframe(gcf);
        writeVideo(video, Frame(j));
    end
    close(video);

    disp('< Done');

end

% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

fclose('all');

disp('Finished');

end

