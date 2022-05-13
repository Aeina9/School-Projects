package com.example.gophernavigate.ui.tools;

import android.os.Bundle;
import android.os.Parcelable;
import android.widget.EditText;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.TextView;
import android.widget.ToggleButton;

import java.io.Serializable;
import java.util.Arrays;
import java.util.Calendar;
import java.util.Hashtable;

import androidx.appcompat.app.AppCompatActivity;
import androidx.viewpager.widget.ViewPager;

import com.example.gophernavigate.R;
import com.example.gophernavigate.ui.Steps.ViewPagerAdapter;

public class ScheduleBuilder extends AppCompatActivity {
    public Hashtable<Integer, String> inttoDay;
    private int dayIndex = 0;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.adding_classes);
        inttoDay = new Hashtable<>();
        inttoDay.put(0, "Sunday");
        inttoDay.put(1, "Monday");
        inttoDay.put(2, "Tuesday");
        inttoDay.put(3, "Wednesday");
        inttoDay.put(4, "Thursday");
        inttoDay.put(5, "Friday");
        inttoDay.put(6, "Saturday");
        Scheduler schedule = new Scheduler();
        for(int i =0; i <7; i++){
            Parcelable[] parcel = getIntent().getParcelableArrayExtra("schedule"+i);
            ScheduledEvent[] temp_events = null;
            if(parcel!=null){
                temp_events = Arrays.copyOf(parcel, 4, ScheduledEvent[].class);
            }
            schedule.events.set(i, temp_events);
        }

        //Scheduler schedule = (Scheduler) getIntent().getParcelableExtra("schedule");
        Calendar cal = Calendar.getInstance();
        int dayNum = cal.get(Calendar.DAY_OF_WEEK)-1;
        String[] day = {inttoDay.get(dayNum)};
        TextView curDay = findViewById(R.id.current_day);
        curDay.setText(day[0]);
        System.out.println(day[0]);
        dayIndex = dayNum;
        Button back = (Button) findViewById(R.id.back_day);
        back.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                dayIndex--;
                if(dayIndex < 0) {
                    dayIndex = 6;
                }
                curDay.setText(inttoDay.get(dayIndex));
                day[0] = inttoDay.get(dayIndex);
                EditText name = (EditText) findViewById(R.id.name_events);
                name.setText("CSCI 5115");
                name = findViewById(R.id.editTextTime);
                name.setText("01");
                name = findViewById(R.id.editTextTime2);
                name.setText("00");
                name = findViewById(R.id.editTextTime3);
                name.setText("03");
                name = findViewById(R.id.editTextTime4);
                name.setText("00");
                name = findViewById(R.id.location_event);
                name.setText("Keller 3-115");

            }
        });
        Button forward = (Button) findViewById(R.id.forward_day);
        forward.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                dayIndex++;
                if(dayIndex > 6) {
                    dayIndex = 0;
                }
                curDay.setText(inttoDay.get(dayIndex));
                day[0] = inttoDay.get(dayIndex);
                EditText name = (EditText) findViewById(R.id.name_events);
                name.setText("CSCI 5115");
                name = findViewById(R.id.editTextTime);
                name.setText("01");
                name = findViewById(R.id.editTextTime2);
                name.setText("00");
                name = findViewById(R.id.editTextTime3);
                name.setText("03");
                name = findViewById(R.id.editTextTime4);
                name.setText("00");
                name = findViewById(R.id.location_event);
                name.setText("Keller 3-115");
            }
        });
        TextView errors = findViewById(R.id.error_message);
        Button complete = (Button) findViewById(R.id.event_added);
        complete.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                EditText name = (EditText) findViewById(R.id.name_events);
                String name_str = name.getText().toString();
                name = findViewById(R.id.editTextTime);
                int timeStartHour = Integer.parseInt(name.getText().toString());
                name = findViewById(R.id.editTextTime2);
                int timeStartMin=Integer.parseInt(name.getText().toString());
                name = findViewById(R.id.editTextTime3);
                int timeEndHour=Integer.parseInt(name.getText().toString());;
                name = findViewById(R.id.editTextTime4);
                int timeEndMin=Integer.parseInt(name.getText().toString());
                ToggleButton IsAM = findViewById(R.id.toggleButton);
                String startHalf = IsAM.getText().toString();
                IsAM = findViewById(R.id.toggleButton2);
                String endHalf = IsAM.getText().toString();
                name = findViewById(R.id.location_event);
                String location = name.getText().toString();
                String errorText = "";
                boolean valid = true;
                if(name_str.length()>10){
                    errorText+="Name is too large. ";
                    valid = false;
                }else if (name_str.length()<1){
                    errorText+="Name is too small. ";
                    valid = false;
                }
                if(isGreaterTime(timeStartHour, timeStartMin, startHalf, timeEndHour, timeEndMin, endHalf)<=0){
                    errorText+="End comes before start time or is equal. ";
                    valid = false;
                }
                if(timeStartHour<1||timeStartHour>12||timeStartMin<0||timeStartMin>60){
                    errorText+="Start out of bounds. ";
                    valid = false;
                }
                if(timeEndHour<1||timeEndHour>12||timeEndMin<0||timeEndMin>60){
                    errorText+="End out of bounds. ";
                    valid = false;
                }
                boolean isFull= true;
                for(int i =0; i<4; i++){
                    if(schedule.events.get(dayIndex)[i]==null){
                        //errorText+="Too many classes. ";
                        isFull = false;
                    }
                }
                if(isFull){
                    errorText+="Too many classes. ";
                    valid = false;
                }

                /*for(int i = 0; i<schedule.events.get(dayIndex).size(); i++){
                    boolean startcorrespond =
                    if(valid==true&&(schedule.events.get(dayIndex).get(i).gettheName()==name_str||
                                    )
                }*/
                if(valid==true){
                    String fullstartTime;
                    if(timeStartMin<10&&timeStartHour<10){
                        fullstartTime = "0"+timeStartHour+":0"+timeStartMin+startHalf;
                    }else if(timeStartMin<10){
                        fullstartTime = ""+timeStartHour+":0"+timeStartMin+startHalf;
                    }else if(timeStartHour<10){
                        fullstartTime = "0"+timeStartHour+":"+timeStartMin+startHalf;
                    } else{
                        fullstartTime = ""+timeStartHour+":"+timeStartMin+startHalf;
                    }
                    String fullendTime;
                    if(timeEndMin<10&&timeEndHour<10){
                        fullendTime = "0"+timeEndHour+":0"+timeEndMin+endHalf;
                    }else if(timeEndMin<10){
                        fullendTime = ""+timeEndHour+":0"+timeEndMin+endHalf;
                    }else if(timeEndHour<10){
                        fullendTime = "0"+timeEndHour+":"+timeEndMin+endHalf;
                    }else{
                        fullendTime = ""+timeEndHour+":"+timeEndMin+endHalf;
                    }
                    schedule.addItem(day[0], fullstartTime, fullendTime, name_str, location);
                    errorText+="Class added. ";
                    Intent output = new Intent();
                    Bundle bundle = new Bundle();
                    for(int i =0; i < 7; i++){
                        //intent.putExtra("schedule"+i, mainSchedule.events.get(i));
                        bundle.putParcelableArray("schedule"+i, schedule.events.get(i));
                    }
                    output.putExtras(bundle);
                    /*Intent output = new Intent();
                    Bundle bundle = new Bundle();
                    bundle.putSerializable("newSchedule", schedule);
                    output.putExtras(bundle);*/
                    setResult(RESULT_OK, output);
                    finish();
                }
                errors.setText(errorText);
            }
        });

        return;
    }
    private int isGreaterTime(int startHour, int startMin, String startHalf, int endHour, int endMin, String endHalf){
        int startTMins;
        if(startHour==12){
            startTMins = startMin;
        }else {
            startTMins = startHour * 60 + startMin;
        }
        if(startHalf.compareTo("PM")==0){
            startTMins+=12*60;
            //System.out.println("here1");
        }

        int endTMins;
        if(startHour==12){
            endTMins = endMin;
        }else{
            endTMins = endHour * 60 + endMin;
        }
        if(endHalf.compareTo("PM")==0){
            endTMins+=12*60;
            //System.out.println("here2");
        }
        if(endTMins>startTMins){
            return 1;
        }else if(endTMins<startTMins){
            return -1;
        }else{
            return 0;
        }
    }
}
