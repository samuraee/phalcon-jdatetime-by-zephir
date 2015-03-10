# Phalcon jDatetime (هجری شمسی)

jDatetime (Hijri Shamsi / Jalali Date) implemention as a PHP extension powered by zephir language

This extension released as a part of [Tartan framework](https://github.com/tartanpro/tartan) (Extended Phalcon Framework)

Requirements
------------

To compile zephir-parser:

* [Zephir 0.6.0+](https://github.com/phalcon/zephir) (Used only for compiling extension)
* PHP 5.2+

Copyright (C) 2013 [Aboozar Ghaffari](http://tartan.pro)  
Part of [Tartan framework](https://github.com/tartanpro/tartan)
  
Installation
------------

install [zephir](https://github.com/phalcon/zephir) 

Clone the tartan extension repository

```bash
git clone https://github.com/tartanpro/phalcon-jdatetime
```

Go to cloned repository path

```bash
# cd phalcon-jdatetime
```

Compile the extension:

```bash
# zephir build
```

add `extension=tartan.so` to your `php.ini` file

restart your webserver (apache / php-fpm / ...)

Usage
-----

Initializing class

```php
use Tartan\Datetime;

$date = new DateTime(); //Creates a new instance
// or
$date = new \Tartan\DateTime();
```

Initializing class with parameters
[List of all valid timezones](http://www.php.net/manual/en/timezones.php)

```php
/*
 * @package Tartan
 * @author Aboozar Ghaffari
 * @param convert bool Converts numbers to Farsi/Persian
 * @param jalali bool Converts date to Jalali
 * @param timezone string Timezone string
 */

$date = new \Tartan\DateTime(true, true, 'Asia/Tehran');
```

Static usage

```php
echo \Tartan\DateTime::date('l j F Y', false, false, true, 'Asia/Tehran');
```

`date` method

```php
$date = new \Tartan\DateTime(true, true, 'Asia/Tehran');
echo $date->date("l j F Y H:i");
```

`gDate` method

```php
$date->gDate("Y-m-d", time(), 'Asia/Tehran');
```

'strftime` method

```php
$date->strftime("%x %H", time(), false, true, 'America/New_York');
```

`mktime` method

```php
$time = $date->mktime(0,0,0,10,2,1368);
//
$time = $date->mktime(0,0,0,10,2,1368);
echo $date->date("l j F Y", $time); //output:‬ شنبه ۲ دی ۱۳۶۸
```

`checkdate` method

```php
$date->checkdate(10, 21, 1390); // Return true
$date->checkdate(9, 31, 1390); // Return false
```

##Resources
- [List of supported timezones](http://www.php.net/manual/en/timezones.php)   
- [Project page in phpclasses.org](http://www.phpclasses.org/jdatetime)   

##Support This Project
  
[![Donate via Paypal](https://www.paypalobjects.com/en_US/i/btn/btn_donate_SM.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=LXEL22GFTXTKN)

Inspired by jDatetime class by [jDateime](https://github.com/sallar/jDateTime) by [Sallar Kaboli](http://sallar.me) 

Original Jalali to Gregorian (and vice versa) convertor:  
Copyright (C) 2000  Roozbeh Pournader and Mohammad Toossi

    Copyright (C) 2003-2013 Sallar Kaboli

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    1- The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.
    
    2- THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
    OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.

