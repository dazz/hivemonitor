<?php

use Symfony\Component\Console\Input\InputArgument;
use Symfony\Component\Console\Input\InputInterface;
use Symfony\Component\Console\Output\OutputInterface;

$console = new \Symfony\Component\Console\Application('yes', 'no');

$console
    ->register('microfone')
    ->setDefinition([
        new InputArgument('duration', InputArgument::OPTIONAL, 'duration of sound sample', 300),
        new InputArgument('samplerate', InputArgument::OPTIONAL, 'sample rate of sound sample', 20000)
    ])
    ->setDescription('microfone')
    ->setCode(
        function (InputInterface $input, OutputInterface $output) {
            $date = new \DateTime('now');

            $path = '/home/pi/apidictor/records';
            $folder = sprintf('%s/%s', $path, $date->format('Y-m-d'));

            if (file_exists($folder) == false) {
                mkdir($folder, 0777, true);
            }

            $output->writeln($folder);

            $filename = sprintf(
                '%s/%s_%s.wav',
                $folder,
                $date->format('Y-m-d_H-i-s'),
                substr((string)microtime(), 2, 8)
            );

            $recordCommand = sprintf(
                'arecord -d %s  -r %s -t wav -D default --disable-softvol --disable-resample %s',
                $input->getArgument('duration'),
                $input->getArgument('samplerate'),
                $filename
            );

            exec($recordCommand, $out);

            $output->writeln($recordCommand);
            $output->writeln($out);
        }
    );

$console
    ->register('fft:band')
    ->setDefinition([
        new InputArgument('wavefile', InputArgument::REQUIRED, 'filename of sound sample'),
        new InputArgument('lowpass', InputArgument::REQUIRED, 'lowpass of sound sample'),
        new InputArgument('highpass', InputArgument::REQUIRED, 'highpass of sound sample'),
    ])
    ->setDescription('run fft on soundfile')
    ->setCode(
        function (InputInterface $input, OutputInterface $output) use ($app) {

            $wavefile = $input->getArgument('wavefile');
            $lowpass = $input->getArgument('lowpass');
            $highpass = $input->getArgument('highpass');

            $meanLoadness = $app['fft.band']($wavefile, $lowpass, $highpass);

            $dateAndTime = new \DateTime();
            $data = [
                'wavefile'   => $wavefile,
                'lowpass'    => (int) $lowpass,
                'highpass'   => (int) $highpass,
                'mean_db'    => (float) $meanLoadness,
                'date'       => $app['dbDate']($dateAndTime),
                'timestamp'  => $dateAndTime->getTimestamp(),
            ];
            $output->writeln(json_encode($data));

//            $app['couchdb']('apidictor')->put($data['timestamp'].'', $data);
        }
    );

return $console;
