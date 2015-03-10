namespace Tartan;

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

    public static function say()
    {
    	//var_dump(self::toGregorian(1393, 12, 18));
        var_dump(self::toJalali(2015, 03, 10));
    }


    /**
     * Gregorian to Jalali Conversion
     * Copyright (C) 2000  Roozbeh Pournader and Mohammad Toossi
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
     * Division
     */
    private static function div(var a, var b) -> int
    {
        return intval (a / b);
    }
}