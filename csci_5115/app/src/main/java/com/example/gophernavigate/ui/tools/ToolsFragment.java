package com.example.gophernavigate.ui.tools;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.os.Parcelable;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.TextView;

import androidx.annotation.Nullable;
import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.Observer;
import androidx.lifecycle.ViewModelProviders;

import java.time.LocalDate;
import java.time.Month;
import java.util.Arrays;

import com.example.gophernavigate.NavigateActivity;
import com.example.gophernavigate.R;

public class ToolsFragment extends Fragment {

    private ToolsViewModel toolsViewModel;
    private View root;
    public Scheduler mainSchedule = new Scheduler();

    public View onCreateView(@NonNull LayoutInflater inflater,
                             ViewGroup container, Bundle savedInstanceState) {
        toolsViewModel =
                ViewModelProviders.of(this).get(ToolsViewModel.class);
        root = inflater.inflate(R.layout.fragment_tools, container, false);
        //final TextView textView = root.findViewById(R.id.text_tools);
        content();
        return root;
    }
    public void content(){
        TextView month = root.findViewById(R.id.month);
        LocalDate currentdate = LocalDate.now();
        Month curMonth = currentdate.getMonth();
        month.setText("Month:\n"+curMonth+" 2022");
        /*TextView test = root.findViewById(R.id.sunItem1);
        test.setBackgroundColor(0xFF7A0019);
        test.setText("CSCI 5115\n5:00PM\n7:00PM");
        test.setTextColor(0xFFFFFFFF);*/
        toolsViewModel.getText().observe(this, new Observer<String>() {
            @Override
            public void onChanged(@Nullable String s) {
                //textView.setText(s);
            }
        });
        Button destroy = (Button) root.findViewById(R.id.clear_schedule);

        destroy.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //mainSchedule.deleteAll();
                AlertDialog.Builder builder = new AlertDialog.Builder(getContext());
                builder.setCancelable(true);
                builder.setTitle("Are You Sure You Want to Clear Schedule?");
                //builder.setMessage("Message");
                builder.setPositiveButton("Confirm",
                        new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int which) {
                                mainSchedule.deleteAll();
                                content();
                            }
                        });
                builder.setNegativeButton(android.R.string.cancel, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        //mainSchedule.deleteAll();
                    }
                });

                AlertDialog dialog = builder.create();
                dialog.show();
            }
        });
        Button impSched = (Button) root.findViewById(R.id.import_schedule);
        impSched.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mainSchedule.deleteAll();
                mainSchedule.addItem("monday", "8:00AM", "10:00AM", "CSCI 3081", "Keller 2-140");
                mainSchedule.addItem("tuesday", "2:30PM", "3:45PM", "CSCI 4707", "Smith 331");
                mainSchedule.addItem("tuesday", "5:30PM", "6:45PM", "CSCI 5115", "Keller 3-115");
                mainSchedule.addItem("wednesday", "1:00PM", "2:15PM", "CSCI 4041", "Keller 2-209");
                mainSchedule.addItem("thursday", "1:00PM", "2:15PM", "CSCI 4041", "Keller 2-209");
                mainSchedule.addItem("thursday", "5:30PM", "6:45PM", "CSCI 5115", "Keller 3-115");
                content();
            }
        });
        Button next_class = (Button) root.findViewById(R.id.next_class);
        next_class.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(getContext(), NavigateActivity.class);
                startActivity(intent);
                content();
            }
        });
        Button edit = (Button) root.findViewById(R.id.edit_elements);
        edit.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(getContext(), ScheduleEditor.class);
                Bundle bundle = new Bundle();

                for(int i =0; i < 7; i++){
                    //intent.putExtra("schedule"+i, mainSchedule.events.get(i));
                    bundle.putParcelableArray("schedule"+i, mainSchedule.events.get(i));
                }
                intent.putExtras(bundle);
                startActivityForResult(intent, 1501);
            }
        });
        Button start = (Button) root.findViewById(R.id.add_element);
        //mainSchedule.addItem("monday","1:00","2:00", "eaef","eafe");
        start.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(getContext(), ScheduleBuilder.class);
                Bundle bundle = new Bundle();

                for(int i =0; i < 7; i++){
                    //intent.putExtra("schedule"+i, mainSchedule.events.get(i));
                    bundle.putParcelableArray("schedule"+i, mainSchedule.events.get(i));
                }
                intent.putExtras(bundle);
                //startActivity(intent);
                startActivityForResult(intent, 1500);
            }
        });
        if(mainSchedule.events.get(0)[0]==null){
            TextView sun1 = root.findViewById(R.id.sundayItem1);
            sun1.setBackgroundColor(0x00ffb71e);
            sun1.setText("");
            sun1.setTextColor(0x00000000);
        }
        if(mainSchedule.events.get(0)[1]==null){
            TextView sun1 = root.findViewById(R.id.sundayItem2);
            sun1.setBackgroundColor(0x00ffb71e);
            sun1.setText("");
            sun1.setTextColor(0x00FFFFFF);
        }
        if(mainSchedule.events.get(0)[2]==null){
            TextView sun1 = root.findViewById(R.id.sundayItem3);
            sun1.setBackgroundColor(0x00ffb71e);
            sun1.setText("");
            sun1.setTextColor(0x00FFFFFF);
        }
        if(mainSchedule.events.get(0)[3]==null){
            TextView sun1 = root.findViewById(R.id.sundayItem4);
            sun1.setBackgroundColor(0x00ffb71e);
            sun1.setText("");
            sun1.setTextColor(0x00FFFFFF);
        }
        if(mainSchedule.events.get(1)[0]==null){
            TextView sun1 = root.findViewById(R.id.mondayItem1);
            sun1.setBackgroundColor(0x007A0019);
            sun1.setText("");
            sun1.setTextColor(0x00FFFFFF);
        }
        if(mainSchedule.events.get(1)[1]==null){
            TextView sun1 = root.findViewById(R.id.mondayItem2);
            sun1.setBackgroundColor(0x007A0019);
            sun1.setText("");
            sun1.setTextColor(0x00FFFFFF);
        }
        if(mainSchedule.events.get(1)[2]==null){
            TextView sun1 = root.findViewById(R.id.mondayItem3);
            sun1.setBackgroundColor(0x007A0019);
            sun1.setText("");
            sun1.setTextColor(0x00FFFFFF);
        }
        if(mainSchedule.events.get(1)[3]==null){
            TextView sun1 = root.findViewById(R.id.mondayItem4);
            sun1.setBackgroundColor(0x007A0019);
            sun1.setText("");
            sun1.setTextColor(0x00FFFFFF);
        }
        if(mainSchedule.events.get(2)[0]==null){
            TextView sun1 = root.findViewById(R.id.tuesdayItem1);
            sun1.setBackgroundColor(0x00ffb71e);
            sun1.setText("");
            sun1.setTextColor(0x00FFFFFF);
        }
        if(mainSchedule.events.get(2)[1]==null){
            TextView sun1 = root.findViewById(R.id.tuesdayItem2);
            sun1.setBackgroundColor(0x00ffb71e);
            sun1.setText("");
            sun1.setTextColor(0x00FFFFFF);
        }
        if(mainSchedule.events.get(2)[2]==null){
            TextView sun1 = root.findViewById(R.id.tuesdayItem3);
            sun1.setBackgroundColor(0x00ffb71e);
            sun1.setText("");
            sun1.setTextColor(0x00FFFFFF);
        }
        if(mainSchedule.events.get(2)[3]==null){
            TextView sun1 = root.findViewById(R.id.tuesdayItem4);
            sun1.setBackgroundColor(0x00ffb71e);
            sun1.setText("");
            sun1.setTextColor(0x00FFFFFF);
        }
        if(mainSchedule.events.get(3)[0]==null){
            TextView sun1 = root.findViewById(R.id.wednesdayItem1);
            sun1.setBackgroundColor(0x007A0019);
            sun1.setText("");
            sun1.setTextColor(0x00FFFFFF);
        }
        if(mainSchedule.events.get(3)[1]==null){
            TextView sun1 = root.findViewById(R.id.wednesdayItem2);
            sun1.setBackgroundColor(0x007A0019);
            sun1.setText("");
            sun1.setTextColor(0x00FFFFFF);
        }
        if(mainSchedule.events.get(3)[2]==null){
            TextView sun1 = root.findViewById(R.id.wednesdayItem3);
            sun1.setBackgroundColor(0x007A0019);
            sun1.setText("");
            sun1.setTextColor(0x00FFFFFF);
        }
        if(mainSchedule.events.get(3)[3]==null){
            TextView sun1 = root.findViewById(R.id.wednesdayItem4);
            sun1.setBackgroundColor(0x007A0019);
            sun1.setText("");
            sun1.setTextColor(0x00FFFFFF);
        }
        if(mainSchedule.events.get(4)[0]==null){
            TextView sun1 = root.findViewById(R.id.thursdayItem1);
            sun1.setBackgroundColor(0x00ffb71e);
            sun1.setText("");
            sun1.setTextColor(0x00FFFFFF);
        }
        if(mainSchedule.events.get(4)[1]==null){
            TextView sun1 = root.findViewById(R.id.thursdayItem2);
            sun1.setBackgroundColor(0x00ffb71e);
            sun1.setText("");
            sun1.setTextColor(0x00FFFFFF);
        }
        if(mainSchedule.events.get(4)[2]==null){
            TextView sun1 = root.findViewById(R.id.thursdayItem3);
            sun1.setBackgroundColor(0x00ffb71e);
            sun1.setText("");
            sun1.setTextColor(0x00FFFFFF);
        }
        if(mainSchedule.events.get(4)[3]==null){
            TextView sun1 = root.findViewById(R.id.thursdayItem4);
            sun1.setBackgroundColor(0x00ffb71e);
            sun1.setText("");
            sun1.setTextColor(0x00FFFFFF);
        }
        if(mainSchedule.events.get(5)[0]==null){
            TextView sun1 = root.findViewById(R.id.fridayItem1);
            sun1.setBackgroundColor(0x007A0019);
            sun1.setText("");
            sun1.setTextColor(0x00FFFFFF);
        }
        if(mainSchedule.events.get(5)[1]==null){
            TextView sun1 = root.findViewById(R.id.fridayItem2);
            sun1.setBackgroundColor(0x007A0019);
            sun1.setText("");
            sun1.setTextColor(0x00FFFFFF);
        }
        if(mainSchedule.events.get(5)[2]==null){
            TextView sun1 = root.findViewById(R.id.fridayItem3);
            sun1.setBackgroundColor(0x007A0019);
            sun1.setText("");
            sun1.setTextColor(0x00FFFFFF);
        }
        if(mainSchedule.events.get(5)[3]==null){
            TextView sun1 = root.findViewById(R.id.fridayItem4);
            sun1.setBackgroundColor(0x007A0019);
            sun1.setText("");
            sun1.setTextColor(0x00FFFFFF);
        }
        if(mainSchedule.events.get(6)[0]==null){
            TextView sun1 = root.findViewById(R.id.saturdayItem1);
            sun1.setBackgroundColor(0x00ffb71e);
            sun1.setText("");
            sun1.setTextColor(0x00FFFFFF);
        }
        if(mainSchedule.events.get(6)[1]==null){
            TextView sun1 = root.findViewById(R.id.saturdayItem2);
            sun1.setBackgroundColor(0x00ffb71e);
            sun1.setText("");
            sun1.setTextColor(0x00FFFFFF);
        }
        if(mainSchedule.events.get(6)[2]==null){
            TextView sun1 = root.findViewById(R.id.saturdayItem3);
            sun1.setBackgroundColor(0x00ffb71e);
            sun1.setText("");
            sun1.setTextColor(0x00FFFFFF);
        }
        if(mainSchedule.events.get(6)[3]==null){
            TextView sun1 = root.findViewById(R.id.saturdayItem4);
            sun1.setBackgroundColor(0x00ffb71e);
            sun1.setText("");
            sun1.setTextColor(0x00FFFFFF);
        }
        if(mainSchedule.events.get(0)[0]!=null){
            TextView sun1 = root.findViewById(R.id.sundayItem1);
            sun1.setBackgroundColor(0xFFffb71e);
            sun1.setText(mainSchedule.events.get(0)[0].toString());
            sun1.setTextColor(0xFF000000);
        }
        if(mainSchedule.events.get(0)[1]!=null){
            TextView sun1 = root.findViewById(R.id.sundayItem2);
            sun1.setBackgroundColor(0xFFffb71e);
            sun1.setText(mainSchedule.events.get(0)[0].toString());
            sun1.setTextColor(0xFF000000);
        }
        if(mainSchedule.events.get(0)[2]!=null){
            TextView sun1 = root.findViewById(R.id.sundayItem3);
            sun1.setBackgroundColor(0xFFffb71e);
            sun1.setText(mainSchedule.events.get(0)[0].toString());
            sun1.setTextColor(0xFF000000);
        }
        if(mainSchedule.events.get(0)[3]!=null){
            TextView sun1 = root.findViewById(R.id.sundayItem4);
            sun1.setBackgroundColor(0xFFffb71e);
            sun1.setText(mainSchedule.events.get(0)[0].toString());
            sun1.setTextColor(0xFF000000);
        }
        if(mainSchedule.events.get(1)[0]!=null){
            TextView sun1 = root.findViewById(R.id.mondayItem1);
            sun1.setBackgroundColor(0xFF7A0019);
            sun1.setText(mainSchedule.events.get(1)[0].toString());
            sun1.setTextColor(0xFFFFFFFF);
        }
        if(mainSchedule.events.get(1)[1]!=null){
            TextView sun1 = root.findViewById(R.id.mondayItem2);
            sun1.setBackgroundColor(0xFF7A0019);
            sun1.setText(mainSchedule.events.get(1)[1].toString());
            sun1.setTextColor(0xFFFFFFFF);
        }
        if(mainSchedule.events.get(1)[2]!=null){
            TextView sun1 = root.findViewById(R.id.mondayItem3);
            sun1.setBackgroundColor(0xFF7A0019);
            sun1.setText(mainSchedule.events.get(1)[2].toString());
            sun1.setTextColor(0xFFFFFFFF);
        }
        if(mainSchedule.events.get(1)[3]!=null){
            TextView sun1 = root.findViewById(R.id.mondayItem4);
            sun1.setBackgroundColor(0xFF7A0019);
            sun1.setText(mainSchedule.events.get(1)[3].toString());
            sun1.setTextColor(0xFFFFFFFF);
        }
        if(mainSchedule.events.get(2)[0]!=null){
            TextView sun1 = root.findViewById(R.id.tuesdayItem1);
            sun1.setBackgroundColor(0xFFffb71e);
            sun1.setText(mainSchedule.events.get(2)[0].toString());
            sun1.setTextColor(0xFF000000);
        }
        if(mainSchedule.events.get(2)[1]!=null){
            TextView sun1 = root.findViewById(R.id.tuesdayItem2);
            sun1.setBackgroundColor(0xFFffb71e);
            sun1.setText(mainSchedule.events.get(2)[1].toString());
            sun1.setTextColor(0xFF000000);
        }
        if(mainSchedule.events.get(2)[2]!=null){
            TextView sun1 = root.findViewById(R.id.tuesdayItem3);
            sun1.setBackgroundColor(0xFFffb71e);
            sun1.setText(mainSchedule.events.get(2)[2].toString());
            sun1.setTextColor(0xFF000000);
        }
        if(mainSchedule.events.get(2)[3]!=null){
            TextView sun1 = root.findViewById(R.id.tuesdayItem4);
            sun1.setBackgroundColor(0xFFffb71e);
            sun1.setText(mainSchedule.events.get(2)[3].toString());
            sun1.setTextColor(0xFF000000);
        }
        if(mainSchedule.events.get(3)[0]!=null){
            TextView sun1 = root.findViewById(R.id.wednesdayItem1);
            sun1.setBackgroundColor(0xFF7A0019);
            sun1.setText(mainSchedule.events.get(3)[0].toString());
            sun1.setTextColor(0xFFFFFFFF);
        }
        if(mainSchedule.events.get(3)[1]!=null){
            TextView sun1 = root.findViewById(R.id.wednesdayItem2);
            sun1.setBackgroundColor(0xFF7A0019);
            sun1.setText(mainSchedule.events.get(3)[1].toString());
            sun1.setTextColor(0xFFFFFFFF);
        }
        if(mainSchedule.events.get(3)[2]!=null){
            TextView sun1 = root.findViewById(R.id.wednesdayItem3);
            sun1.setBackgroundColor(0xFF7A0019);
            sun1.setText(mainSchedule.events.get(3)[2].toString());
            sun1.setTextColor(0xFFFFFFFF);
        }
        if(mainSchedule.events.get(3)[3]!=null){
            TextView sun1 = root.findViewById(R.id.wednesdayItem4);
            sun1.setBackgroundColor(0xFF7A0019);
            sun1.setText(mainSchedule.events.get(3)[3].toString());
            sun1.setTextColor(0xFFFFFFFF);
        }
        if(mainSchedule.events.get(4)[0]!=null){
            TextView sun1 = root.findViewById(R.id.thursdayItem1);
            sun1.setBackgroundColor(0xFFffb71e);
            sun1.setText(mainSchedule.events.get(4)[0].toString());
            sun1.setTextColor(0xFF000000);
        }
        if(mainSchedule.events.get(4)[1]!=null){
            TextView sun1 = root.findViewById(R.id.thursdayItem2);
            sun1.setBackgroundColor(0xFFffb71e);
            sun1.setText(mainSchedule.events.get(4)[1].toString());
            sun1.setTextColor(0xFF000000);
        }
        if(mainSchedule.events.get(4)[2]!=null){
            TextView sun1 = root.findViewById(R.id.thursdayItem3);
            sun1.setBackgroundColor(0xFFffb71e);
            sun1.setText(mainSchedule.events.get(4)[2].toString());
            sun1.setTextColor(0xFF000000);
        }
        if(mainSchedule.events.get(4)[3]!=null){
            TextView sun1 = root.findViewById(R.id.thursdayItem4);
            sun1.setBackgroundColor(0xFFffb71e);
            sun1.setText(mainSchedule.events.get(4)[3].toString());
            sun1.setTextColor(0xFF000000);
        }
        if(mainSchedule.events.get(5)[0]!=null){
            TextView sun1 = root.findViewById(R.id.fridayItem1);
            sun1.setBackgroundColor(0xFF7A0019);
            sun1.setText(mainSchedule.events.get(5)[0].toString());
            sun1.setTextColor(0xFFFFFFFF);
        }
        if(mainSchedule.events.get(5)[1]!=null){
            TextView sun1 = root.findViewById(R.id.fridayItem2);
            sun1.setBackgroundColor(0xFF7A0019);
            sun1.setText(mainSchedule.events.get(5)[1].toString());
            sun1.setTextColor(0xFFFFFFFF);
        }
        if(mainSchedule.events.get(5)[2]!=null){
            TextView sun1 = root.findViewById(R.id.fridayItem3);
            sun1.setBackgroundColor(0xFF7A0019);
            sun1.setText(mainSchedule.events.get(5)[2].toString());
            sun1.setTextColor(0xFFFFFFFF);
        }
        if(mainSchedule.events.get(5)[3]!=null){
            TextView sun1 = root.findViewById(R.id.fridayItem4);
            sun1.setBackgroundColor(0xFF7A0019);
            sun1.setText(mainSchedule.events.get(5)[3].toString());
            sun1.setTextColor(0xFFFFFFFF);
        }
        if(mainSchedule.events.get(6)[0]!=null){
            TextView sun1 = root.findViewById(R.id.saturdayItem1);
            sun1.setBackgroundColor(0xFFffb71e);
            sun1.setText(mainSchedule.events.get(6)[0].toString());
            sun1.setTextColor(0xFF000000);
        }
        if(mainSchedule.events.get(6)[1]!=null){
            TextView sun1 = root.findViewById(R.id.saturdayItem2);
            sun1.setBackgroundColor(0xFFffb71e);
            sun1.setText(mainSchedule.events.get(6)[1].toString());
            sun1.setTextColor(0xFF000000);
        }
        if(mainSchedule.events.get(6)[2]!=null){
            TextView sun1 = root.findViewById(R.id.saturdayItem3);
            sun1.setBackgroundColor(0xFFffb71e);
            sun1.setText(mainSchedule.events.get(6)[2].toString());
            sun1.setTextColor(0xFF000000);
        }
        if(mainSchedule.events.get(6)[3]!=null){
            TextView sun1 = root.findViewById(R.id.saturdayItem4);
            sun1.setBackgroundColor(0xFFffb71e);
            sun1.setText(mainSchedule.events.get(6)[3].toString());
            sun1.setTextColor(0xFF000000);
        }
    }
    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) {

        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == 1500 && resultCode == Activity.RESULT_OK && data != null) {
            //mainSchedule = (Scheduler) data.getExtras().getSerializable("newSchedule");
            for(int i =0; i <7; i++){
                Parcelable[] parcel = data.getParcelableArrayExtra("schedule"+i);
                ScheduledEvent[] temp_events = null;
                if(parcel!=null){
                    temp_events = Arrays.copyOf(parcel, 4, ScheduledEvent[].class);
                }
                mainSchedule.events.set(i, temp_events);
            }

        }
        if (requestCode == 1501 && resultCode == Activity.RESULT_OK && data != null) {
            //mainSchedule = (Scheduler) data.getExtras().getSerializable("newSchedule");
            for(int i =0; i <7; i++){
                Parcelable[] parcel = data.getParcelableArrayExtra("schedule"+i);
                ScheduledEvent[] temp_events = null;
                if(parcel!=null){
                    temp_events = Arrays.copyOf(parcel, 4, ScheduledEvent[].class);
                }
                mainSchedule.events.set(i, temp_events);
            }

        }

        content();
    }
}