package com.example.gophernavigate.ui.tools;

import android.os.Parcel;
import android.os.Parcelable;

import java.util.ArrayList;

public class ScheduledEvent implements Parcelable {
    private String start;
    private String end;
    private String name;
    private String location;
    public ScheduledEvent(String start_, String end_, String name_, String location_){
        this.start = start_;
        this.end= end_;
        this.name = name_;
        this.location = location_;
    }

    protected ScheduledEvent(Parcel in) {
        start = in.readString();
        end = in.readString();
        name = in.readString();
        location = in.readString();
    }

    public static final Creator<ScheduledEvent> CREATOR = new Creator<ScheduledEvent>() {
        @Override
        public ScheduledEvent createFromParcel(Parcel in) {
            return new ScheduledEvent(in);
        }

        @Override
        public ScheduledEvent[] newArray(int size) {
            return new ScheduledEvent[size];
        }
    };

    public String getStart(){
        return start;
    }
    public String getEnd(){
        return end;
    }
    public String gettheName(){
        return name;
    }
    public String getLocation(){
        return location;
    }

    @Override
    public int describeContents() {
        return 0;
    }

    @Override
    public void writeToParcel(Parcel parcel, int i) {
        parcel.writeString(start);
        parcel.writeString(end);
        parcel.writeString(name);
        parcel.writeString(location);
    }
    public String toString(){
        return name+"\n"+start+"\n"+end+"\n"+location;
    }
    public String toStringFormatted(){return name+"\n"+start+"-"+end+"\n"+location;}

    public int[] getTimeInformation(){
        int[] timeItems = new int[6];
        String nums = start.substring(0,4);
        String startHalf = start.substring(4,6);
        int isPM = 0;
        if(startHalf=="AM"){
            isPM = 0;
        }else if(startHalf=="PM"){
            isPM = 1;
        }
        String[] start = nums.split(":");
        timeItems[0] = Integer.parseInt(start[0]);
        timeItems[1] = Integer.parseInt(start[1]);
        timeItems[2] = isPM;
        nums = end.substring(0,4);
        startHalf = end.substring(4,6);
        isPM = 0;
        if(startHalf=="AM"){
            isPM = 0;
        }else if(startHalf=="PM"){
            isPM = 1;
        }
        start = nums.split(":");
        timeItems[3] = Integer.parseInt(start[0]);
        timeItems[4] = Integer.parseInt(start[1]);
        timeItems[5] = isPM;
        return timeItems;
    }
}
