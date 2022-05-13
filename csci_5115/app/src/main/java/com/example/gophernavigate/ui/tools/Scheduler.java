package com.example.gophernavigate.ui.tools;

import android.os.Parcel;
import android.os.Parcelable;

import com.google.android.gms.common.util.ArrayUtils;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Hashtable;
import java.util.List;
import java.util.Locale;

public class Scheduler  {
    public ArrayList<ScheduledEvent[]> events;
    public Hashtable<String, Integer> dayToint;
    public Scheduler(){
        events = new ArrayList<>();
        for(int i = 0; i < 7; i++ ){
            events.add(new ScheduledEvent[4]);
        }
        dayToint = new Hashtable<>();
        dayToint.put("sunday", 0);
        dayToint.put("monday", 1);
        dayToint.put("tuesday", 2);
        dayToint.put("wednesday", 3);
        dayToint.put("thursday", 4);
        dayToint.put("friday", 5);
        dayToint.put("saturday", 6);
    }



    /*public static final Creator<Scheduler> CREATOR = new Creator<Scheduler>() {
        @Override
        public Scheduler createFromParcel(Parcel in) {
            return new Scheduler(in);
        }

        @Override
        public Scheduler[] newArray(int size) {
            return new Scheduler[size];
        }
    };*/

    public void addItem(String day, String start, String end, String name, String location){
        day = day.toLowerCase();
        ScheduledEvent[] tempEvents;
        switch (day){
            case "sunday":
                tempEvents = events.get(0);
                for(int i = 0; i < 4; i++){
                    if(tempEvents[i]==null){
                        tempEvents[i]=(new ScheduledEvent(start, end, name, location));
                        break;
                    }
                }
                events.set(0, tempEvents);
                break;
            case "monday":
                tempEvents = events.get(1);
                for(int i = 0; i < 4; i++){
                    if(tempEvents[i]==null){
                        tempEvents[i]=(new ScheduledEvent(start, end, name, location));
                        break;
                    }
                }
                events.set(1, tempEvents);
                break;
            case "tuesday":
                tempEvents = events.get(2);
                for(int i = 0; i < 4; i++){
                    if(tempEvents[i]==null){
                        tempEvents[i]=(new ScheduledEvent(start, end, name, location));
                        break;
                    }
                }
                events.set(2, tempEvents);
                break;
            case "wednesday":
                tempEvents = events.get(3);
                for(int i = 0; i < 4; i++){
                    if(tempEvents[i]==null){
                        tempEvents[i]=(new ScheduledEvent(start, end, name, location));
                        break;
                    }
                }
                events.set(3, tempEvents);
                break;
            case "thursday":
                tempEvents = events.get(4);
                for(int i = 0; i < 4; i++){
                    if(tempEvents[i]==null){
                        tempEvents[i]=(new ScheduledEvent(start, end, name, location));
                        break;
                    }
                }
                events.set(4, tempEvents);
                break;
            case "friday":
                tempEvents = events.get(5);
                for(int i = 0; i < 4; i++){
                    if(tempEvents[i]==null){
                        tempEvents[i]=(new ScheduledEvent(start, end, name, location));
                        break;
                    }
                }
                events.set(5, tempEvents);
                break;
            case "saturday":
                tempEvents = events.get(6);
                for(int i = 0; i < 4; i++){
                    if(tempEvents[i]==null){
                        tempEvents[i]=(new ScheduledEvent(start, end, name, location));
                        break;
                    }
                }
                events.set(6, tempEvents);
                break;
            default:
                System.out.println("invalid day");
                break;
        }
    }
    public void deleteItem(String day, int index){
        String tempDay = day.toLowerCase();
        ScheduledEvent[] tempItems = new ScheduledEvent[3];
        for(int i=0; i <index; i++){
            tempItems[i] = events.get(dayToint.get(tempDay))[i];
        }
        for(int i=index+1; i<3; i++){
            tempItems[i-1] = events.get(dayToint.get(tempDay))[i];
        }
        for(int i =0; i<3; i++){
            events.get(dayToint.get(tempDay))[i] = tempItems[i];
        }
        events.get(dayToint.get(tempDay))[2] = events.get(dayToint.get(tempDay))[3];
        events.get(dayToint.get(tempDay))[3] = null;
    }
    public void deleteAll(){
        events = new ArrayList<>();
        for(int i = 0; i < 7; i++ ){
            events.add(new ScheduledEvent[4]);
        }
    }

    /*@Override
    public int describeContents() {
        return 0;
    }

    @Override
    public void writeToParcel(Parcel parcel, int i) {
        int daysInWeek = events.size();
        for(int j =0; j<daysInWeek; j++){
            parcel.writeTypedArray(events.get(j), i);
        }
    }*/
}
