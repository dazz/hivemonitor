<?php
use dazz\HiveMonitor\Provider;

$app = new \Silex\Application();

$app['root'] = dirname(__DIR__);

$app['fft.band'] = $app->protect(
    function ($wavefile, $highpass, $lowpass) use ($app) {
        exec(sprintf('sudo %s/bin/fft_band.py %s %s %s', $app['root'], $wavefile, $highpass, $lowpass), $out);
        return $out[0];
    }
);

$app->register(new Provider\SagServiceProvider(),
    [
        'cdb.timeout.open' => 3,
        'cdb.timeout.readwrite' => 3,
        'cdb.options' => [
            'apidictor' => [
                'username' => 'apidictor',
                'password' => 'rotcidipa',
                'host'     => 'localhost',
                'port'     => '5984',
                'dbname'   => 'apidictor',
            ],
        ]
    ]
);

$app['dbDate'] = $app->protect(
    function (\DateTime $dateTime) {
        return [
            (int) $dateTime->format('Y'),
            (int) $dateTime->format('m'),
            (int) $dateTime->format('d'),
            (int) $dateTime->format('H'),
            (int) $dateTime->format('i'),
            (int) $dateTime->format('s'),
        ];
    }
);


return $app;
