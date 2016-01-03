<?php
namespace dazz\HiveMonitor\Provider;

use Silex\Application;
use Silex\ServiceProviderInterface;

class SagServiceProvider implements ServiceProviderInterface
{
    public function register(Application $app)
    {
        $app['couchdb'] = $app->protect(
            function ($dbName) use ($app) {

                if (empty($app['cdb.options'][$dbName])) {
                    throw new \InvalidArgumentException('Database "' . $dbName . '" is not properly configured!');
                }
                $dbOptions = $app['cdb.options'][$dbName];

                $sag = new \Sag($dbOptions['host'], $dbOptions['port']);
                $sag->setHTTPAdapter(\Sag::$HTTP_CURL);
                if (isset($app['cdb.timeout.open'])) {
                    $sag->setOpenTimeout($app['cdb.timeout.open']);
                }
                if (isset($app['cdb.timeout.readwrite'])) {
                    $sag->setRWTimeout($app['cdb.timeout.readwrite']);
                }
                $sag->login($dbOptions['username'], $dbOptions['password']);
                $sag->setDatabase($dbOptions['dbname']);

                return $sag;
            }
        );
    }

    public function boot(Application $app)
    {
    }
}
