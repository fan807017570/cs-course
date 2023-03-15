select count(distinct period_no) as total_period_count ,count(distinct msg_id) as total_count from ac_std_record_07
        where tran_date ='20230307' and business_type ='DEP';


    select count(*) from (  select count(distinct msg_id) as total_count from ac_std_record_07 where tran_date ='20230307' and business_type ='DEP') t;


ALTER TABLE ac_std_record_24 DROP INDEX `idx_ac_std_record_3`;
ALTER TABLE ac_std_record_24 ADD  KEY `idx_ac_std_record_3` (`tran_date`,`business_type`,`msg_id`);

create index idx_ac_std_record_2 on ac_std_record_01 (`tran_date`,`post_status`);


select count(*) as total_count , 0 as total_period_count from( select distinct msg_id from ac_std_record  where tran_date ='20230324' and business_type='DEP') t;



        select distinct batch_no as batchNo from ac_post where post_date = '20230324';
        