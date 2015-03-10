namespace Tartan;

use DateTime;
use DateTimeZone;

class Datetime
{
    private static jalali; //Use Jalali Date, If set to false, falls back to gregorian
    private static convert; //Convert numbers to Farsi characters in utf-8
    private static timezone; //Timezone String e.g Asia/Tehran, Defaults to Server Timezone Settings
    private static temp;

    /**
     * jDateTime::Constructor
     *
     * Pass these parameteres when creating a new instance
     * of this Class, and they will be used as defaults.
     * e.g $obj = new Tartan\DateTime(false, true, 'Asia/Tehran');
     * To use system defaults pass null for each one or just
     * create the object without any parameters.
     *
     * @package Tartan
     * @author Aboozar Ghaffari <me@tartan.pro>
     * @param convert bool Converts numbers to Farsi
     * @param jalali bool Converts date to Jalali
     * @param timezone string Timezone string
     */
    public function __construct(bool convert = true, bool jalali = true, string timezone = "")
    {
        let self::jalali   = jalali;
        let self::convert  = convert;
        let self::timezone = timezone;
    }

    /**
     * jDateTime::Date
     *
     * Formats and returns given timestamp just like php's
     * built in date() function.
     * e.g:
     * $obj->date("Y-m-d H:i", time());
     * $obj->date("Y-m-d", time(), false, false, 'America/New_York');
     *
     * @package Tartan
     * @author Aboozar Ghaffari <me@tartan.pro>
     * @param $format string Acceps format string based on: php.net/date
     * @param $stamp int Unix Timestamp (Epoch Time)
     * @param $convert bool (Optional) forces convert action. pass null to use system default
     * @param $jalali bool (Optional) forces jalali conversion. pass null to use system default
     * @param $timezone string (Optional) forces a different timezone. pass null to use system default
     * @return string Formatted input
     */
    public static function date(string! format, stamp = false, convert = null, jalali = null, timezone = null)
    {
        array intact, intactValues;
        //Timestamp + Timezone
        let stamp    = (stamp !== false) ? stamp : time();
        let timezone = (timezone != null) ? timezone : ((self::timezone != null) ? self::timezone : date_default_timezone_get());
        var obj;
        let obj      = new DateTime("@" . stamp, new DateTimeZone(timezone));

        obj->setTimezone(new DateTimeZone(timezone));
        
        if ( (self::jalali === false && jalali === null) || jalali === false ) {
            return obj->format(format);
        }
        else {
            array chars;
            let chars = [];
            //Find what to replace
            let chars  = (preg_match_all("/([a-zA-Z]{1})/", format, chars)) ? chars[0] : [];
            
            //Intact Keys
            let intact = ["B","h","H","g","G","i","s","I","U","u","Z","O","P"];
            let intact = self::filterArray(chars, intact);
            let intactValues = [];
            var k, v;
            for k, v in intact {
                let intactValues[k] = obj->format(v);
            }
            //End Intact Keys
            //Changed Keys
            int year, month, day;
            let year  = intval(obj->format("Y"));
            let month = intval(obj->format("n"));
            let day   = intval(obj->format("j"));

            var jParts;
            let jParts = self::toJalali(year, month, day);

            int jyear, jmonth, jday;
            let jyear  = intval(jParts[0]);
            let jmonth = intval(jParts[1]);
            let jday   = intval(jParts[2]);

            array keys;
            let keys = ["d","D","j","l","N","S","w","z","W","F","m","M","n","t","L","o","Y","y","a","A","c","r","e","T"];
            let keys = self::filterArray(chars, keys, ["z"]);
            array values;
            let values = [];

            var key;
            for k, key in keys {
                let v = "";
                switch (key) {
                    //Day
                    case "d":
                        let v = sprintf("%02d", jday);
                        break;
                    case "D":
                        let v = self::getDayNames(obj->format("D"), true);
                        break;
                    case "j":
                        let v = jday;
                        break;
                    case "l":
                        let v = self::getDayNames(obj->format("l"));
                        break;
                    case "N":
                        let v = self::getDayNames(obj->format("l"), false, 1, true);
                        break;
                    case "S":
                        let v = "ام";
                        break;
                    case "w":
                        let v = self::getDayNames(obj->format("l"), false, 1, true) - 1;
                        break;
                    case "z":
                        if (jmonth > 6) {
                            let v = 186 + ((jmonth - 6 - 1) * 30) + jday;
                        }
                        else {
                            let v = ((jmonth - 1) * 31) + jday;
                        }
                        let self::temp["z"] = v;
                        break;
                    //Week
                    case "W":
                        let v = is_int(self::temp["z"] / 7) ? (self::temp["z"] / 7) : intval(self::temp["z"] / 7 + 1);
                        break;
                    //Month
                    case "F":
                        let v = self::getMonthNames(jmonth);
                        break;
                    case "m":
                        let v = sprintf("%02d", jmonth);
                        break;
                    case "M":
                        let v = self::getMonthNames(jmonth, true);
                        break;
                    case "n":
                        let v = jmonth;
                        break;
                    case "t":
                        if (jmonth >= 1 && jmonth <= 6) {
                            let v = 31;
                        } elseif (jmonth >= 7 && jmonth <= 11) {
                            let v = 30;
                        } elseif(jmonth == 12 && jyear % 4 == 3) {
                            let v = 30;
                        } elseif (jmonth == 12 && jyear % 4 != 3) {
                            let v = 29;
                        }
                        break;
                    //Year
                    case "L":
                        var tmpObj;
                        let tmpObj = new DateTime("@".strval(time() - 31536000));
                        let v = tmpObj->format("L");
                        break;
                    case "o":
                    case "Y":
                        let v = jyear;
                        break;
                    case "y":
                        let v = jyear % 100;
                        break;
                    //Time
                    case "a":
                        let v = (obj->format("a") == "am") ? "ق.ظ" : "ب.ظ";
                        break;
                    case "A":
                        let v = (obj->format("A") == "AM") ? "قبل از ظهر" : "بعد از ظهر";
                        break;
                    //Full Dates
                    case "c":
                        let v  = jyear . "-" . sprintf("%02d", jmonth) . "-" . sprintf("%02d", jday) . "T";
                        let v .= obj->format("H") . ":" . obj->format("i") . ":" . obj->format("s") . obj->format("P");
                        break;
                    case "r":
                        let v  = self::getDayNames(obj->format("D"), true) . ", " . sprintf("%02d", jday) . " " . self::getMonthNames(jmonth, true);
                        let v .= " " . jyear . " " . obj->format("H") . ":" . obj->format("i") . ":" . obj->format("s") . " " . obj->format("P");
                        break;
                    //Timezone
                    case "e":
                        let v = obj->format("e");
                        break;
                    case "T":
                        let v = obj->format("T");
                        break;
                }
                let values[k] = v;
            }
            //End Changed Keys
            //Merge
            let keys   = array_merge(intact, keys);
            let values = array_merge(intactValues, values);
            //Return
            var ret;
            let ret = strtr(format, array_combine(keys, values));
            return
                (convert === false ||
                (convert === null && self::convert === false) ||
                ( jalali === false || jalali === null && self::jalali === false ))
                ? ret : self::convertNumbers(ret);
        }
    }

    /**
     * Gregorian to Jalali Conversion
     * Copyright (C) 2000  Roozbeh Pournader and Mohammad Toossi
     * @package Tartan
     * @author Aboozar Ghaffari <me@tartan.pro>
     * @param g_y integer Gregorian year
     * @param g_m integer Gregorian month
     * @param g_d integer Gregorian day
     */
    public static function toJalali(g_y, g_m, g_d)
    {
        array g_days_in_month, j_days_in_month;
        int gy, gm, gd, g_day_no, jy, jm, jd, j_day_no, i;
        var j_np;
        let g_days_in_month = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31];
        let j_days_in_month = [31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 29];

        let gy = g_y - 1600;
        let gm = g_m - 1;
        let gd = g_d - 1;

        let g_day_no = 365 * gy + self::div(gy + 3, 4) - self::div(gy + 99, 100) + self::div(gy + 399, 400);

        let i = 0;
        while i < gm {
            let g_day_no += g_days_in_month[i];
            let i++;
        }

        if (gm > 1 && ((gy % 4 == 0 && gy % 100 != 0) || (gy % 400 == 0))) {
            let g_day_no++;
        }

        let g_day_no += gd;
        let j_day_no = g_day_no - 79;

        let j_np = self::div(j_day_no, 12053);
        let j_day_no = j_day_no % 12053;

        let jy = 979 + 33 * j_np + 4 * self::div(j_day_no, 1461);
        let j_day_no %= 1461;

        if (j_day_no >= 366) {
            let jy += self::div(j_day_no - 1, 365);
            let j_day_no = (j_day_no - 1) % 365;
        }

        let i = 0;

        while (i < 11 && j_day_no >= j_days_in_month[i]) {
            let j_day_no -= j_days_in_month[i];
            let i++;
        }

        let jm = i + 1;
        let jd = j_day_no + 1;
        return [jy, jm, jd];
    }

    /**
     * Jalali to Gregorian Conversion
     * Copyright (C) 2000  Roozbeh Pournader and Mohammad Toossi
     *
     * @package Tartan
     * @author Aboozar Ghaffari <me@tartan.pro>
     * @param j_y integer Jalali year
     * @param j_m integer Jalali month
     * @param j_d integer Jalali day
     */
    public static function toGregorian(int! j_y, int! j_m, int! j_d) -> array
    {
    	array g_days_in_month, j_days_in_month;
    	int jy, jm, jd, j_day_no, g_day_no, gy, gm, gd, i, j, a;
    	boolean leap;

        let g_days_in_month = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31];
        let j_days_in_month = [31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 29];

        let jy = j_y - 979;
        let jm = j_m - 1;
        let jd = j_d - 1;

        let j_day_no = 365 * jy + self::div(jy, 33) * 8 + self::div( jy % 33 + 3, 4);

        let i = 0;
        while i < jm {
            let j_day_no += j_days_in_month[i];
            let i++;
        }

        let j_day_no += jd;
        let g_day_no = j_day_no + 79;

        let gy = 1600 + 400 * self::div(g_day_no, 146097);
        let g_day_no = g_day_no % 146097;

        let leap = true;
        if (g_day_no >= 36525) {
            let g_day_no = g_day_no - 1;
            let gy += 100 * self::div(g_day_no,  36524);
            let g_day_no = g_day_no % 36524;
            if (g_day_no >= 365) {
                let g_day_no = g_day_no + 1;
            }
            else {
                let leap = false;
            }
        }

        let gy += 4 * self::div(g_day_no, 1461);
        let g_day_no %= 1461;

        if (g_day_no >= 366) {
            let leap = false;
            let g_day_no = g_day_no - 1;
            let gy += self::div(g_day_no, 365);
            let g_day_no = g_day_no % 365;
        }

        let i = 0;
        let j = count(g_days_in_month) - 1;

        while i < j {
            if (i == 1 && leap) {
                let a = 1;
            } else {
                let a = 0;
            }

            if (g_day_no >= g_days_in_month[i] + a) {
                let g_day_no -= g_days_in_month[i] + a;
            } else {
                break;
            }
            let i++;
        }

        let gm = i + 1;
        let gd = g_day_no + 1;
        return [gy, gm, gd];
    }

        /**
     * jDateTime::Checkdate
     *
     * Checks the validity of the date formed by the arguments.
     * A date is considered valid if each parameter is properly defined.
     * works like php's built in checkdate() function.
     * Leap years are taken into consideration.
     * e.g:
     * $obj->checkdate(10, 21, 1390); // Return true
     * $obj->checkdate(9, 31, 1390);  // Return false
     *
     * You can force gregorian checkdate if system default is jalali and you
     * need to check based on gregorian date
     * $check = $obj->checkdate(12, 31, 2011, false);
     *
     * @author Omid Pilevar
     * @param $month int The month is between 1 and 12 inclusive.
     * @param $day int The day is within the allowed number of days for the given month.
     * @param $year int The year is between 1 and 32767 inclusive.
     * @param $jalali bool (Optional) pass false if you want to input gregorian time
     * @return bool
     */
    public static function checkdate(int! month, int! day, int! year, jalali = null) -> boolean
    {
        var epoch, ret;

        //Defaults
        let month = (month == 0) ? self::date("n") : month;
        let day   = (day   == 0) ? self::date("j") : day;
        let year  = (year  == 0) ? self::date("Y") : year;
        
        //Check if its jalali date
        if ( jalali === true || (jalali === null && self::jalali === true) )
        {
            let epoch = self::mktime(0, 0, 0, month, day, year);
            
            if ( self::date("Y-n-j", epoch, false) == year."-".month."-".day ) {
                let ret = true;
            }
            else{
                let ret = false; 
            }
        }
        else //Gregorian Date
        { 
            let ret = checkdate(month, day, year);
        }
        
        //Return
        return ret;
    }

    /**
     * jDateTime::Mktime
     *
     * Creates a Unix Timestamp (Epoch Time) based on given parameters
     * works like php's built in mktime() function.
     * e.g:
     * $time = $obj->mktime(0,0,0,2,10,1368);
     * $obj->date("Y-m-d", $time); //Format and Display
     * $obj->date("Y-m-d", $time, false, false); //Display in Gregorian !
     *
     * You can force gregorian mktime if system default is jalali and you
     * need to create a timestamp based on gregorian date
     * $time2 = $obj->mktime(0,0,0,12,23,1989, false);
     *
     * @author Aboozar Ghaffari <me@tartan.pro>
     * @param $hour int Hour based on 24 hour system
     * @param $minute int Minutes
     * @param $second int Seconds
     * @param $month int Month Number
     * @param $day int Day Number
     * @param $year int Four-digit Year number eg. 1390
     * @param $jalali bool (Optional) pass false if you want to input gregorian time
     * @param $timezone string (Optional) acceps an optional timezone if you want one
     * @return int Unix Timestamp (Epoch Time)
     */
    public static function mktime(int! hour, int! minute, int! second, int! month, int! day, int! year, jalali = null, timezone = null) -> int
    {
        var gParts, obj;
        string date;
        //Defaults
        let month = (month == 0) ? self::date("m") : month;
        let day   = (day   == 0) ? self::date("d") : day;
        let year  = (year  == 0) ? self::date("Y") : year;
        //Convert to Gregorian if necessary
        if ( jalali === true || (jalali === null && self::jalali === true) ) {
            let gParts= self::toGregorian(year, month, day);
            let year = intval(gParts[0]);
            let month = intval(gParts[1]);
            let day = intval(gParts[2]);
        }
        //Create a new object and set the timezone if available
        let date = year . "-" . sprintf("%02d", month) . "-" . sprintf("%02d", day) . " " . hour . ":" . minute . ":" . second;
        if ( self::timezone != null || timezone != null ) {
            let obj = new DateTime(date, new DateTimeZone((timezone != null) ? timezone : self::timezone));
        }
        else {
            let obj = new DateTime(date);
        }
        //Return
        return obj->format("U");
    }

    /**
     * jDateTime::Strftime
     *
     * Format a local time/date according to locale settings
     * built in strftime() function.
     * e.g:
     * $obj->strftime("%x %H", time());
     * $obj->strftime("%H", time(), false, false, 'America/New_York');
     *
     * @author Omid Pilevar
     * @param $format string Acceps format string based on: php.net/date
     * @param $stamp int Unix Timestamp (Epoch Time)
     * @param $convert bool (Optional) forces convert action. pass null to use system default
     * @param $jalali bool (Optional) forces jalali conversion. pass null to use system default
     * @param $timezone string (Optional) forces a different timezone. pass null to use system default
     * @return string Formatted input
     */
    public static function strftime(string! format, stamp = false, convert = null, jalali = null, timezone = null)
    {
        array str_format_code, date_format_code; 
        let str_format_code = [
            "%a", "%A", "%d", "%e", "%j", "%u", "%w",
            "%U", "%V", "%W",
            "%b", "%B", "%h", "%m",
            "%C", "%g", "%G", "%y", "%Y",
            "%H", "%I", "%l", "%M", "%p", "%P", "%r", "%R", "%S", "%T", "%X", "%z", "%Z",
            "%c", "%D", "%F", "%s", "%x",
            "%n", "%t", "%%"
        ];
        
        let date_format_code = [
            "D", "l", "d", "j", "z", "N", "w",
            "W", "W", "W",
            "M", "F", "M", "m",
            "y", "y", "y", "y", "Y",
            "H", "h", "g", "i", "A", "a", "h:i:s A", "H:i", "s", "H:i:s", "h:i:s", "H", "H",
            "D j M H:i:s", "d/m/y", "Y-m-d", "U", "d/m/y",
            "\n", "\t", "%"
        ];
        //Change Strftime format to Date format
        let format = str_replace(str_format_code, date_format_code, format);
        //Convert to date
        return self::date(format, stamp, convert, jalali, timezone);
    }

    /**
     * Division
     * @package Tartan
     * @author Aboozar Ghaffari <me@tartan.pro>
     * @param a integer
     * @param b integer
     */
    private static function div(var a, var b) -> int
    {
        return intval (a / b);
    }

    /**
     * Substring helper
     *
     * @package Tartan
     * @author Aboozar Ghaffari <me@tartan.pro>
     * @param str string text
     * @param start integer start index
     * @param len integer length
     */
    private static function substr(string str, int start, int len) -> string
    {
        if (function_exists("mb_substr")){
            return mb_substr(str, start, len, "UTF-8");
        }
        else{
            return substr(str, start, len * 2);
        }
    }

    /**
     * Converts latin numbers to farsi script
     * @package Tartan
     * @author Aboozar Ghaffari <me@tartan.pro>
     * @param matches array array of digits for convertion
     */
    private static function convertNumbers(array matches) -> array
    {
        array farsi_array, english_array;

        let farsi_array   = ["۰", "۱", "۲", "۳", "۴", "۵", "۶", "۷", "۸", "۹"];
        let english_array = ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9"];
        return str_replace(english_array, farsi_array, matches);
    }

    /**
     * Returns correct names for months
     *
     * @package Tartan
     * @author Aboozar Ghaffari <me@tartan.pro>
     * @param month integer
     * @param shorten boolean
     * @param len integer
     */
    private static function getMonthNames(int! month, boolean shorten = false, int len = 3)
    {
        array months;
        var ret;
        // Convert
        let months = ["فروردین", "اردیبهشت", "خرداد", "تیر", "مرداد", "شهریور", "مهر", "آبان", "آذر", "دی", "بهمن", "اسفند"];
        let ret    = months[month - 1];
        // Return
        return (shorten == true) ? self::substr(ret, 0, len) : ret;
    }

    /**
     * Returns correct names for week days
     *
     * @package Tartan
     * @author Aboozar Ghaffari <me@tartan.pro>
     * @param day integer
     * @param shorten boolean
     * @param len integer
     * @param numeric boolean
     */
    private static function getDayNames(day, boolean! shorten = false, int! len = 1, boolean! numeric = false)
    {
        array days;
        let days = [
            "sat" : [1, "شنبه"],
            "sun" : [2, "یکشنبه"],
            "mon" : [3, "دوشنبه"],
            "tue" : [4, "سه شنبه"],
            "wed" : [5, "چهارشنبه"],
            "thu" : [6, "پنجشنبه"],
            "fri" : [7, "جمعه"]
        ];
        let day = substr(strtolower(day), 0, 3);
        let day = days[day];
        return (numeric == true) ? day[0] : ((shorten == true) ? self::substr(day[1], 0, len) : day[1]);
    }

    /**
     * Filters out an array
     *
     * @package Tartan
     * @author Aboozar Ghaffari <me@tartan.pro>
     * @param needle array
     * @param heystack array
     * @param always array
     */
    private static function filterArray(array needle, array heystack, array always = []) -> array
    {
        return array_intersect(array_merge(needle, always), heystack);
    }

    /**
     * jDateTime::gDate
     *
     * Same as jDateTime::Date method
     * but this one works as a helper and returns Gregorian Date
     * in case someone doesn't like to pass all those false arguments
     * to Date method.
     *
     * e.g. $obj->gDate("Y-m-d") //Outputs: 2011-05-05
     *      $obj->date("Y-m-d", false, false, false); //Outputs: 2011-05-05
     *      Both return the exact same result.
     *
     * @author Aboozar Ghaffari <me@tartan.pro>
     * @param $format string Acceps format string based on: php.net/date
     * @param $stamp int Unix Timestamp (Epoch Time)
     * @param $timezone string (Optional) forces a different timezone. pass null to use system default
     * @return string Formatted input
     */
    public static function gDate(string format, stamp = false, timezone = null)
    {
        return self::date(format, stamp, false, false, timezone);
    }
}