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
     * e.g $obj = new jDateTime(false, true, 'Asia/Tehran');
     * To use system defaults pass null for each one or just
     * create the object without any parameters.
     *
     * @author Aboozar Ghaffari
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
    	var_dump(self::toGregorian(1393, 12, 18));
    }

    /**
     * Jalali to Gregorian Conversion
     *
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

        var_dump(j_day_no);

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
        echo g_day_no. "\n";

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


      //   for i in range(0, count(g_days_in_month) - 1) {
    		// if (i == 1 && leap) {
    		// 	let a = 1;
    		// } else {
    		// 	let a = 0;
    		// }

    		// if (g_day_no >= g_days_in_month[i] + a) {
    		// 	let g_day_no -= g_days_in_month[i] + a;
    		// } else {
    		// 	break;
    		// }
      //   }


        // for ($i = 0; $g_day_no >= $g_days_in_month[$i] + ($i == 1 && $leap); $i++) {
        //     $g_day_no -= $g_days_in_month[$i] + ($i == 1 && $leap);
        // }

        let gm = i + 1;
        let gd = g_day_no + 1;
        return [gy, gm, gd];
    }

    /**
     * Division
     */
    private static function div(var a, var b) -> int
    {
        return (int) (a / b);
    }
}