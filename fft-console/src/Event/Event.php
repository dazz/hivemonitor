<?php
/**
 * A modified MIT License (MIT)
 * Copyright © 2014
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so., subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * Neither the Software, nor any derivative product, shall be used to operate weapons,
 * military nuclear facilities, life support or other mission critical applications
 * where human life or property may be at stake or endangered.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
namespace dazz\HiveMonitor\Event;

/**
 * Class Event
 * @package dazz\HiveMonitor\Event
 */
abstract class Event
{
    protected $data = [];
    protected $dateTime;

    public function __construct()
    {
        $this->dateTime = new \DateTime('now');
    }
    /**
     * "device": "mac",
    "location": {"lon": 0.3, "lat": 0.4},
    "event": "name",
    "data": {},
    "datetime": ["2014", "12", "24", "00", "01", "44"]
     */

    protected function getDateTime()
    {
        return [
            (int) $this->dateTime->format('Y'),
            (int) $this->dateTime->format('m'),
            (int) $this->dateTime->format('d'),
            (int) $this->dateTime->format('H'),
            (int) $this->dateTime->format('i'),
            (int) $this->dateTime->format('s'),
        ];
    }

    public abstract function getName();
    public abstract function getData();

    protected function asJson()
    {
        return json_encode(
            [
                'event' => $this->getName(),
                'data' => $this->getData(),
                'datetime' => $this->getDateTime(),
            ]
        );
    }
} 