package utils;

class DateUtils {

    public static function getDayOfYear() {
        var now = Date.now();
        var year = now.getFullYear();
        var nowTime = Date.now().getTime();
        var yearStartTime = new Date(year, 0, 1, 0, 0, 0).getTime();
        var divider = 24 * 3600 * 1000;
        return Math.floor((nowTime - yearStartTime) / divider);
    }

    public static function getWeekOfYear(): Int {
        var now = Date.now();
        var year = now.getFullYear();
        var dayOfYear = getDayOfYear();
        var dayOfWeek = now.getDay();
        var newyearDayOfWeek = new Date(year, 0, 1, 0, 0, 0).getDay();
        var weekNum = Math.floor((dayOfYear + 6) / 7);
        if (dayOfWeek < newyearDayOfWeek) {
            weekNum++;
        }
        return weekNum;
    }
}