totalImpulse = 0;

for stepCounter = 1 : nTimeSteps-1
    totalImpulse = totalImpulse + (particleData{1, forceIdx}(stepCounter, 1) + particleData{1, forceIdx}(stepCounter+1, 1))*timeStep/2;
end

totalAngularMomentum = zeros(nTimeSteps, 3);

for counter = 1 : nParticles
    totalAngularMomentum = totalAngularMomentum + particleData{counter, angularMomentumIdx};
end