package com.example.gophernavigate.ui.tools;

import android.content.Intent;
import android.os.Bundle;
import android.os.Parcelable;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import androidx.drawerlayout.widget.DrawerLayout;
import androidx.navigation.NavController;
import androidx.navigation.Navigation;
import androidx.navigation.ui.AppBarConfiguration;
import androidx.navigation.ui.NavigationUI;

import com.example.gophernavigate.R;
import com.google.android.material.floatingactionbutton.FloatingActionButton;
import com.google.android.material.navigation.NavigationView;

import java.util.Arrays;
import java.util.Calendar;
import java.util.Hashtable;

public class ScheduleEditor extends AppCompatActivity {
    public Hashtable<Integer, String> inttoDay;
    private int dayIndex = 0;

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.edit_classes);
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
        Calendar cal = Calendar.getInstance();
        int dayNum = cal.get(Calendar.DAY_OF_WEEK)-1;
        String[] day = {inttoDay.get(dayNum)};
        TextView curDay = findViewById(R.id.current_day);
        curDay.setText(day[0]);
        System.out.println(day[0]);
        dayIndex = dayNum;
        int numPop = 0;
        for(int i =0; i<4; i++){
            if(schedule.events.get(dayIndex)[i]!=null){
                System.out.println(i);
                System.out.println(schedule.events.get(dayIndex)[i].toString());
                numPop++;
            }
        }
        FloatingActionButton rem1 = (FloatingActionButton) findViewById(R.id.remove1);
        FloatingActionButton rem2 = (FloatingActionButton) findViewById(R.id.remove2);
        FloatingActionButton rem3 = (FloatingActionButton) findViewById(R.id.remove3);
        FloatingActionButton rem4 = (FloatingActionButton) findViewById(R.id.remove4);
        TextView tex1 = (TextView) findViewById(R.id.textView1);
        TextView tex2 = (TextView) findViewById(R.id.textView2);
        TextView tex3 = (TextView) findViewById(R.id.textView3);
        TextView tex4 = (TextView) findViewById(R.id.textView4);
        if(numPop==1){
            rem2.setAlpha(0);
            rem2.getBackground().setAlpha(0);
            rem3.setAlpha(0);
            rem3.getBackground().setAlpha(0);
            rem4.setAlpha(0);
            rem4.getBackground().setAlpha(0);
            tex1.setText(schedule.events.get(dayIndex)[0].toStringFormatted());
        }else if(numPop==2){
            rem3.setAlpha(0);
            rem3.getBackground().setAlpha(0);
            rem4.setAlpha(0);
            rem4.getBackground().setAlpha(0);
            tex1.setText(schedule.events.get(dayIndex)[0].toStringFormatted());
            //rem2.setAlpha(1);
            tex2.setText(schedule.events.get(dayIndex)[1].toStringFormatted());
        }else if(numPop==3){
            rem4.getBackground().setAlpha(0);
            rem4.setAlpha(0);
            tex1.setText(schedule.events.get(dayIndex)[0].toStringFormatted());
            //rem2.setAlpha(1);
            tex2.setText(schedule.events.get(dayIndex)[1].toStringFormatted());
            //rem3.setAlpha(1);
            tex3.setText(schedule.events.get(dayIndex)[2].toStringFormatted());
        }else if(numPop==4){
            //rem1.setAlpha(1);
            tex1.setText(schedule.events.get(dayIndex)[0].toStringFormatted());
            //rem2.setAlpha(1);
            tex2.setText(schedule.events.get(dayIndex)[1].toStringFormatted());
            //rem3.setAlpha(1);
            tex3.setText(schedule.events.get(dayIndex)[2].toStringFormatted());
            //rem4.setAlpha(1);
            tex4.setText(schedule.events.get(dayIndex)[3].toStringFormatted());
        }else{
            rem1.getBackground().setAlpha(0);
            rem2.getBackground().setAlpha(0);
            rem3.getBackground().setAlpha(0);
            rem4.getBackground().setAlpha(0);
            rem1.setAlpha(0);
            rem2.setAlpha(0);
            rem3.setAlpha(0);
            rem4.setAlpha(0);
            tex1.setText("");
            tex2.setText("");
            tex3.setText("");
            tex4.setText("");
        }
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
                int numPop = 0;
                for(int i =0; i<4; i++){
                    if(schedule.events.get(dayIndex)[i]!=null){
                        numPop++;
                    }
                }
                if(numPop==1){
                    rem1.setAlpha(1);
                    rem1.getBackground().setAlpha(1);
                    rem2.setAlpha(0);
                    rem2.getBackground().setAlpha(0);
                    rem3.setAlpha(0);
                    rem3.getBackground().setAlpha(0);
                    rem4.setAlpha(0);
                    rem4.getBackground().setAlpha(0);
                    tex1.setText(schedule.events.get(dayIndex)[0].toStringFormatted());
                }else if(numPop==2){
                    rem1.setAlpha(1);
                    rem1.getBackground().setAlpha(1);
                    rem2.setAlpha(1);
                    rem2.getBackground().setAlpha(1);
                    rem3.setAlpha(0);
                    rem3.getBackground().setAlpha(0);
                    rem4.setAlpha(0);
                    rem4.getBackground().setAlpha(0);
                    tex1.setText(schedule.events.get(dayIndex)[0].toStringFormatted());
                    //rem2.setAlpha(1);
                    tex2.setText(schedule.events.get(dayIndex)[1].toStringFormatted());
                }else if(numPop==3){
                    rem1.setAlpha(1);
                    rem1.getBackground().setAlpha(1);
                    rem2.setAlpha(1);
                    rem2.getBackground().setAlpha(1);
                    rem3.setAlpha(1);
                    rem3.getBackground().setAlpha(1);
                    rem4.getBackground().setAlpha(0);
                    rem4.setAlpha(0);
                    tex1.setText(schedule.events.get(dayIndex)[0].toStringFormatted());
                    //rem2.setAlpha(1);
                    tex2.setText(schedule.events.get(dayIndex)[1].toStringFormatted());
                    //rem3.setAlpha(1);
                    tex3.setText(schedule.events.get(dayIndex)[2].toStringFormatted());
                }else if(numPop==4){
                    //rem1.setAlpha(1);
                    tex1.setText(schedule.events.get(dayIndex)[0].toStringFormatted());
                    //rem2.setAlpha(1);
                    tex2.setText(schedule.events.get(dayIndex)[1].toStringFormatted());
                    //rem3.setAlpha(1);
                    tex3.setText(schedule.events.get(dayIndex)[2].toStringFormatted());
                    //rem4.setAlpha(1);
                    tex4.setText(schedule.events.get(dayIndex)[3].toStringFormatted());
                }else{
                    rem1.getBackground().setAlpha(0);
                    rem2.getBackground().setAlpha(0);
                    rem3.getBackground().setAlpha(0);
                    rem4.getBackground().setAlpha(0);
                    rem1.setAlpha(0);
                    rem2.setAlpha(0);
                    rem3.setAlpha(0);
                    rem4.setAlpha(0);
                    tex1.setText("");
                    tex2.setText("");
                    tex3.setText("");
                    tex4.setText("");
                }
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
                int numPop = 0;
                for(int i =0; i<4; i++){
                    if(schedule.events.get(dayIndex)[i]!=null){
                        numPop++;
                    }
                }
                if(numPop==1){
                    rem2.setAlpha(0);
                    rem2.getBackground().setAlpha(0);
                    rem3.setAlpha(0);
                    rem3.getBackground().setAlpha(0);
                    rem4.setAlpha(0);
                    rem4.getBackground().setAlpha(0);
                    tex1.setText(schedule.events.get(dayIndex)[0].toStringFormatted());
                }else if(numPop==2){
                    rem3.setAlpha(0);
                    rem3.getBackground().setAlpha(0);
                    rem4.setAlpha(0);
                    rem4.getBackground().setAlpha(0);
                    tex1.setText(schedule.events.get(dayIndex)[0].toStringFormatted());
                    //rem2.setAlpha(1);
                    tex2.setText(schedule.events.get(dayIndex)[1].toStringFormatted());
                }else if(numPop==3){
                    rem4.getBackground().setAlpha(0);
                    rem4.setAlpha(0);
                    tex1.setText(schedule.events.get(dayIndex)[0].toStringFormatted());
                    //rem2.setAlpha(1);
                    tex2.setText(schedule.events.get(dayIndex)[1].toStringFormatted());
                    //rem3.setAlpha(1);
                    tex3.setText(schedule.events.get(dayIndex)[2].toStringFormatted());
                }else if(numPop==4){
                    //rem1.setAlpha(1);
                    tex1.setText(schedule.events.get(dayIndex)[0].toStringFormatted());
                    //rem2.setAlpha(1);
                    tex2.setText(schedule.events.get(dayIndex)[1].toStringFormatted());
                    //rem3.setAlpha(1);
                    tex3.setText(schedule.events.get(dayIndex)[2].toStringFormatted());
                    //rem4.setAlpha(1);
                    tex4.setText(schedule.events.get(dayIndex)[3].toStringFormatted());
                }else{
                    rem1.getBackground().setAlpha(0);
                    rem2.getBackground().setAlpha(0);
                    rem3.getBackground().setAlpha(0);
                    rem4.getBackground().setAlpha(0);
                    rem1.setAlpha(0);
                    rem2.setAlpha(0);
                    rem3.setAlpha(0);
                    rem4.setAlpha(0);
                    tex1.setText("");
                    tex2.setText("");
                    tex3.setText("");
                    tex4.setText("");
                }
            }
        });

        rem1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v){
                //System.out.println(day[0]);
                if(schedule.events.get(dayIndex)[0]!=null){
                    schedule.deleteItem(day[0], 0);
                    Intent output = new Intent();
                    Bundle bundle = new Bundle();
                    for (int i = 0; i < 7; i++) {
                        //intent.putExtra("schedule"+i, mainSchedule.events.get(i));
                        bundle.putParcelableArray("schedule" + i, schedule.events.get(i));
                    }

                    output.putExtras(bundle);
                    setResult(RESULT_OK, output);
                    finish();
                }
            }
        });
        rem2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v){
                //System.out.println(day[0]);
                if(schedule.events.get(dayIndex)[1]!=null){
                    schedule.deleteItem(day[0], 1);
                    Intent output = new Intent();
                    Bundle bundle = new Bundle();
                    for (int i = 0; i < 7; i++) {
                        //intent.putExtra("schedule"+i, mainSchedule.events.get(i));
                        bundle.putParcelableArray("schedule" + i, schedule.events.get(i));
                    }

                    output.putExtras(bundle);
                    setResult(RESULT_OK, output);
                    finish();
                }
            }
        });
        rem3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v){
                //System.out.println(day[0]);
                if(schedule.events.get(dayIndex)[2]!=null){
                    schedule.deleteItem(day[0], 2);
                    Intent output = new Intent();
                    Bundle bundle = new Bundle();
                    for (int i = 0; i < 7; i++) {
                        //intent.putExtra("schedule"+i, mainSchedule.events.get(i));
                        bundle.putParcelableArray("schedule" + i, schedule.events.get(i));
                    }

                    output.putExtras(bundle);
                    setResult(RESULT_OK, output);
                    finish();
                }
            }
        });
        rem4.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v){
                //System.out.println(day[0]);
                if(schedule.events.get(dayIndex)!=null){
                    schedule.deleteItem(day[0], 3);
                    Intent output = new Intent();
                    Bundle bundle = new Bundle();
                    for (int i = 0; i < 7; i++) {
                        //intent.putExtra("schedule"+i, mainSchedule.events.get(i));
                        bundle.putParcelableArray("schedule" + i, schedule.events.get(i));
                    }

                    output.putExtras(bundle);
                    setResult(RESULT_OK, output);
                    finish();
                }
            }
        });

    }
}
