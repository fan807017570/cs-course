- deadlock case 1

  - mysql-8.0.7

  - table schema

    ```sql
    CREATE TABLE `ac_std_record_01` (
      `id` bigint unsigned NOT NULL AUTO_INCREMENT COMMENT 'id',
      `ac_seq_no` varchar(64) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL COMMENT 'Accounting unified serial number',
      `msg_id` varchar(64) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL COMMENT 'Message id',
      `reference_no` varchar(64) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL COMMENT 'Platform reference number.',
      `ori_reference_no` varchar(64) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin DEFAULT NULL COMMENT 'Original business sequence number ,in reversal scenario, the ori_reference_no is the normal transaction reference number .',
      `biz_seq_no` varchar(64) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL COMMENT 'Business transaction number ',
      `biz_tran_record_id` varchar(64) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL COMMENT 'Business transaction record id ,accounting use this value to trace issue',
      `business_type` varchar(10) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL COMMENT 'Business type ,Deposit: DEP,Loan: NL ,Internal Account:IA ,General Ledger:GL.',
      `channel` varchar(10) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL COMMENT 'Business channel which indicates witch platform the transaction is from ',
      `channel_seq_no` varchar(64) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin DEFAULT NULL COMMENT 'Business channel sequence number .',
      `event_type` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL COMMENT 'Event of business transaction , FEE- charge fee TAX- charge tax TWRN-write off TDIS- disbursement TREP- repayment TTNPL-trun into NPL status  PL TPROV-provision TLMA-limit adjustment TWAV-waive TAMT-amotization TDEBT-debit TCRET-credit TRPTD_PRI-relate party transfer debit for principal TRPTC_PRI-relate party transfer credit for principal TRPTD_INT-relate party transfer debit for interest TRPTC_INT-relate party transfer credit for interest',
      `sub_event_type` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin DEFAULT NULL COMMENT 'Sub event of business transaction.',
      `main_acct_no` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin DEFAULT NULL COMMENT 'Main account number of transaction',
      `loan_number` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin DEFAULT NULL COMMENT 'Loan IOU number.',
      `amt_type` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL COMMENT 'Amount type of transaction',
      `prod_type` varchar(10) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL COMMENT 'Business prod code ',
      `fee_type` varchar(40) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin DEFAULT NULL COMMENT 'Fee product code.',
      `tax_code` varchar(40) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin DEFAULT NULL COMMENT 'Tax product code.',
      `tran_ccy` varchar(10) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL COMMENT 'currency of transaction',
      `amount` decimal(23,4) NOT NULL COMMENT 'transaction amount.',
      `tran_date` varchar(8) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL COMMENT 'Transaction date.',
      `effect_date` varchar(8) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin DEFAULT NULL COMMENT 'Effect date of transaction .',
      `branch` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin DEFAULT NULL COMMENT 'Accounting level branch',
      `tran_branch` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin DEFAULT NULL COMMENT 'branch of transaction',
      `reversal_tran_flag` varchar(1) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL COMMENT 'Reversal transaction flag',
      `narrative` varchar(200) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin DEFAULT NULL COMMENT 'Remark of the business transaction .',
      `rp_type` varchar(10) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL COMMENT 'Relate party types.',
      `rp_code` varchar(10) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL COMMENT 'Relate party code',
      `brp_code` varchar(200) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL COMMENT 'Bank relate party code',
      `tenor` varchar(32) COLLATE utf8mb4_bin DEFAULT NULL COMMENT 'tenor',
      `biz_status` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL COMMENT 'Business status of the transaction .NPL-non performing loan ,WRN-write off ,ODUE-overdue ,NOR-normal ,ZHC-normal',
      `repayment_method` varchar(10) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin DEFAULT NULL COMMENT 'Repayment method. DUE-repayment on time or overdue,EAR-early repayment,FDP-full settled,PDP-partial settled',
      `gl_code` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin DEFAULT NULL COMMENT 'Subject code',
      `batch_flag` varchar(1) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL COMMENT 'Y: from end of batch ,N :does not from end of batch',
      `post_status` varchar(1) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL COMMENT 'I:initial ,P:processing,S:success ,F :failed.',
      `period_no` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin DEFAULT NULL COMMENT 'Period range which the data is located in',
      `user_id` varchar(128) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin DEFAULT NULL COMMENT 'The user who generate the business transaction in GL module ,like maker',
      `author_user_id` varchar(128) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin DEFAULT NULL COMMENT 'The user who generate the business transaction in GL module ,like checker',
      `tran_timestamp` bigint NOT NULL COMMENT 'transaction timestamp of business transaction',
      `create_timestamp` bigint NOT NULL COMMENT 'Create timestamp',
      `update_timestamp` bigint NOT NULL COMMENT 'Update timestamp',
      `version` bigint NOT NULL DEFAULT '0' COMMENT 'version',
      PRIMARY KEY (`id`),
      UNIQUE KEY `uk_ac_std_record_1` (`ac_seq_no`),
      KEY `idx_ac_std_record_3` (`business_type`,`msg_id`),
      KEY `idx_ac_std_record_1` (`tran_date`,`business_type`,`period_no`,`reference_no`),
      KEY `idx_ac_std_record_2` (`tran_date`,`post_status`)
    ) ENGINE=InnoDB AUTO_INCREMENT=19 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_bin COMMENT='Accounting unified access flow table'
    
    ```

  - sql command cause deadlock 

    ```sql
    update ac_std_record_25 set post_status ='S' ,version=version+1, update_timestamp =ROUND(UNIX_TIMESTAMP(CURRENT_TIMESTAMP(4)) * 1000.0)
            where ac_seq_no ='20221125200720010000000000002105' and tran_date ='20221125' and post_status ='I';
     update ac_std_record_25 set post_status ='S' ,version=version+1, update_timestamp =ROUND(UNIX_TIMESTAMP(CURRENT_TIMESTAMP(4)) * 1000.0)
            where ac_seq_no ='20221125200720010000000000001102' and tran_date ='20221125' and post_status ='I';
    ```

    

  - deadlock log  showed by (show engine innodb status)

  ```
  
  
  
  ***************************[ 1. row ]***************************
  ENGINE                | INNODB
  ENGINE_LOCK_ID        | 140517951530576:4611:140517841115488
  ENGINE_TRANSACTION_ID | 871705
  THREAD_ID             | 4541
  EVENT_ID              | 19
  OBJECT_SCHEMA         | accounting
  OBJECT_NAME           | ac_std_record_25
  PARTITION_NAME        | <null>
  SUBPARTITION_NAME     | <null>
  INDEX_NAME            | <null>
  OBJECT_INSTANCE_BEGIN | 140517841115488
  LOCK_TYPE             | TABLE
  LOCK_MODE             | IX
  LOCK_STATUS           | GRANTED
  LOCK_DATA             | <null>
  ***************************[ 2. row ]***************************
  ENGINE                | INNODB
  ENGINE_LOCK_ID        | 140517951530576:3546:30:333:140517841112576
  ENGINE_TRANSACTION_ID | 871705
  THREAD_ID             | 4541
  EVENT_ID              | 19
  OBJECT_SCHEMA         | accounting
  OBJECT_NAME           | ac_std_record_25
  PARTITION_NAME        | <null>
  SUBPARTITION_NAME     | <null>
  INDEX_NAME            | idx_ac_std_record_2
  OBJECT_INSTANCE_BEGIN | 140517841112576
  LOCK_TYPE             | RECORD
  LOCK_MODE             | X,REC_NOT_GAP
  LOCK_STATUS           | WAITING
  LOCK_DATA             | '20221125', 'I', 1
  
  ***************************[ 3. row ]***************************
  ENGINE                | INNODB
  ENGINE_LOCK_ID        | 140517951531384:4611:140517841121760
  ENGINE_TRANSACTION_ID | 871704
  THREAD_ID             | 4548
  EVENT_ID              | 24
  OBJECT_SCHEMA         | accounting
  OBJECT_NAME           | ac_std_record_25
  PARTITION_NAME        | <null>
  SUBPARTITION_NAME     | <null>
  INDEX_NAME            | <null>
  OBJECT_INSTANCE_BEGIN | 140517841121760
  LOCK_TYPE             | TABLE
  LOCK_MODE             | IX
  LOCK_STATUS           | GRANTED
  LOCK_DATA             | <null>
  ***************************[ 4. row ]***************************
  ENGINE                | INNODB
  ENGINE_LOCK_ID        | 140517951531384:3546:30:333:140517841118848
  ENGINE_TRANSACTION_ID | 871704
  THREAD_ID             | 4548
  EVENT_ID              | 24
  OBJECT_SCHEMA         | accounting
  OBJECT_NAME           | ac_std_record_25
  PARTITION_NAME        | <null>
  SUBPARTITION_NAME     | <null>
  INDEX_NAME            | idx_ac_std_record_2
  OBJECT_INSTANCE_BEGIN | 140517841118848
  LOCK_TYPE             | RECORD
  LOCK_MODE             | X
  LOCK_STATUS           | GRANTED
  LOCK_DATA             | '20221125', 'I', 1
  
  ***************************[ 5. row ]***************************
  ENGINE                | INNODB
  ENGINE_LOCK_ID        | 140517951531384:3546:30:334:140517841118848
  ENGINE_TRANSACTION_ID | 871704
  THREAD_ID             | 4548
  EVENT_ID              | 24
  OBJECT_SCHEMA         | accounting
  OBJECT_NAME           | ac_std_record_25
  PARTITION_NAME        | <null>
  SUBPARTITION_NAME     | <null>
  INDEX_NAME            | idx_ac_std_record_2
  OBJECT_INSTANCE_BEGIN | 140517841118848
  LOCK_TYPE             | RECORD
  LOCK_MODE             | X
  LOCK_STATUS           | GRANTED
  LOCK_DATA             | '20221125', 'I', 2
  ***************************[ 6. row ]***************************
  ENGINE                | INNODB
  ENGINE_LOCK_ID        | 140517951531384:3546:8:2:140517841119192
  ENGINE_TRANSACTION_ID | 871704
  THREAD_ID             | 4548
  EVENT_ID              | 24
  OBJECT_SCHEMA         | accounting
  OBJECT_NAME           | ac_std_record_25
  PARTITION_NAME        | <null>
  SUBPARTITION_NAME     | <null>
  INDEX_NAME            | PRIMARY
  OBJECT_INSTANCE_BEGIN | 140517841119192
  LOCK_TYPE             | RECORD
  LOCK_MODE             | X,REC_NOT_GAP
  LOCK_STATUS           | GRANTED
  LOCK_DATA             | 1
  ***************************[ 7. row ]***************************
  ENGINE                | INNODB
  ENGINE_LOCK_ID        | 140517951531384:3546:8:3:140517841119192
  ENGINE_TRANSACTION_ID | 871704
  THREAD_ID             | 4548
  EVENT_ID              | 24
  OBJECT_SCHEMA         | accounting
  OBJECT_NAME           | ac_std_record_25
  PARTITION_NAME        | <null>
  SUBPARTITION_NAME     | <null>
  INDEX_NAME            | PRIMARY
  OBJECT_INSTANCE_BEGIN | 140517841119192
  LOCK_TYPE             | RECORD
  LOCK_MODE             | X,REC_NOT_GAP
  LOCK_STATUS           | GRANTED
  LOCK_DATA             | 2
  ***************************[ 8. row ]***************************
  ENGINE                | INNODB
  ENGINE_LOCK_ID        | 140517951531384:3546:18:3:140517841119536
  ENGINE_TRANSACTION_ID | 871704
  THREAD_ID             | 4548
  EVENT_ID              | 24
  OBJECT_SCHEMA         | accounting
  OBJECT_NAME           | ac_std_record_25
  PARTITION_NAME        | <null>
  SUBPARTITION_NAME     | <null>
  INDEX_NAME            | uk_ac_std_record_1
  OBJECT_INSTANCE_BEGIN | 140517841119536
  LOCK_TYPE             | RECORD
  LOCK_MODE             | X,REC_NOT_GAP
  LOCK_STATUS           | GRANTED
  LOCK_DATA             | '20221125200720010000000000002105', 1 ----会锁id=1 
  ----- deadlock caused by lock resource by step  
  ```

  

  - deadlock analysis 

- deadlock example 2

  - mysql-8.0.7

  - table schema

    ```sql
    CREATE TABLE `bizf_biz_record` (
      `id` bigint NOT NULL AUTO_INCREMENT COMMENT 'primary key',
      `req_biz_no` varchar(64) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL COMMENT 'req biz no',
      `req_sys_no` varchar(64) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin DEFAULT NULL COMMENT 'system seq no',
      `from_app_name` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin DEFAULT NULL COMMENT 'from app name',
      `request` longtext CHARACTER SET utf8mb4 COLLATE utf8mb4_bin COMMENT 'response',
      `response` longtext CHARACTER SET utf8mb4 COLLATE utf8mb4_bin COMMENT 'response',
      `response_class` text CHARACTER SET utf8mb4 COLLATE utf8mb4_bin COMMENT 'response class',
      `service_id` text CHARACTER SET utf8mb4 COLLATE utf8mb4_bin COMMENT 'service id',
      `status` varchar(2) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL COMMENT 'status',
      `protocol` varchar(10) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin DEFAULT NULL COMMENT 'protocol',
      `create_timestamp` bigint NOT NULL COMMENT 'create time',
      `update_timestamp` bigint DEFAULT NULL COMMENT 'update time',
      PRIMARY KEY (`id`),
      UNIQUE KEY `uk_bizf_biz_record_1` (`req_biz_no`)
    ) ENGINE=InnoDB AUTO_INCREMENT=107149 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_bin
    
    ```

    

  - sql statement causing deadlock 

    ```sql
    INSERT INTO bizf_biz_record  ( req_sys_no,
    from_app_name,
    req_biz_no,
    status,
    protocol,
    create_timestamp )  VALUES  ('0101007F0E001C4C00000202D3C5D000', 'deposit-core', '14027617957542416783561845998350', 'P', 'mq', 1678696228332);
    
    INSERT INTO bizf_biz_record  ( req_sys_no,
    from_app_name,
    req_biz_no,
    status,
    protocol,
    create_timestamp )  VALUES  ('0101007F0E001C4C00009612D3C51000', 'deposit-core', '14027617957542416783561888432276', 'P', 'mq', 1678696227519);
    
    
    ```

    

  - deadlock log information

    ```
    ------------------------
    LATEST DETECTED DEADLOCK
    ------------------------
    2023-03-13 15:30:28 0x7f95677fe700
    *** (1) TRANSACTION:
    TRANSACTION 1257598997, ACTIVE 0 sec inserting
    mysql tables in use 1, locked 1
    LOCK WAIT 7 lock struct(s), heap size 1136, 2 row lock(s), undo log entries 1
    MySQL thread id 302734, OS thread handle 140282357118720, query id 76982266 10.162.83.250 bank_test update
    INSERT INTO bizf_biz_record  ( req_sys_no,
    from_app_name,
    req_biz_no,
    
    
    status,
    protocol,
    
    
    create_timestamp )  VALUES  ('0101007F0E001C4C00000202D3C5D000', 'deposit-core', '14027617957542416783561845998350', 'P', 'mq', 1678696228332)
    
    *** (1) HOLDS THE LOCK(S):
    RECORD LOCKS space id 338505 page no 10901 n bits 424 index uk_bizf_biz_record_1 of table `accounting`.`bizf_biz_record` trx id 1257598997 lock mode S locks gap before rec
    Record lock, heap no 290 PHYSICAL RECORD: n_fields 2; compact format; info bits 0
     0: len 30; hex 313430333939383136313736323536313637383335343338383736363239; asc 140399816176256167835438876629; (total 32 bytes);
     1: len 8; hex 80000000000046a9; asc       F ;;
    *** (1) WAITING FOR THIS LOCK TO BE GRANTED:
    RECORD LOCKS space id 338505 page no 10901 n bits 424 index uk_bizf_biz_record_1 of table `accounting`.`bizf_biz_record` trx id 1257598997 lock_mode X locks gap before rec insert intention waiting
    Record lock, heap no 290 PHYSICAL RECORD: n_fields 2; compact format; info bits 0
     0: len 30; hex 313430333939383136313736323536313637383335343338383736363239; asc 140399816176256167835438876629; (total 32 bytes);
     1: len 8; hex 80000000000046a9; asc       F ;;
    
    
    *** (2) TRANSACTION:
    TRANSACTION 1257598963, ACTIVE 1 sec inserting
    mysql tables in use 1, locked 1
    LOCK WAIT 5 lock struct(s), heap size 1136, 2 row lock(s), undo log entries 1
    MySQL thread id 302589, OS thread handle 140280952342272, query id 76982124 10.162.83.250 bank_test update
    INSERT INTO bizf_biz_record  ( req_sys_no,
    from_app_name,
    req_biz_no,
    
    
    status,
    protocol,
    
    
    create_timestamp )  VALUES  ('0101007F0E001C4C00009612D3C51000', 'deposit-core', '14027617957542416783561888432276', 'P', 'mq', 1678696227519)
    
    *** (2) HOLDS THE LOCK(S):
    RECORD LOCKS space id 338505 page no 10901 n bits 424 index uk_bizf_biz_record_1 of table `accounting`.`bizf_biz_record` trx id 1257598963 lock mode S locks gap before rec
    Record lock, heap no 290 PHYSICAL RECORD: n_fields 2; compact format; info bits 0
     0: len 30; hex 313430333939383136313736323536313637383335343338383736363239; asc 140399816176256167835438876629; (total 32 bytes);
     1: len 8; hex 80000000000046a9; asc       F ;;
    *** (2) WAITING FOR THIS LOCK TO BE GRANTED:
    RECORD LOCKS space id 338505 page no 10901 n bits 424 index uk_bizf_biz_record_1 of table `accounting`.`bizf_biz_record` trx id 1257598963 lock_mode X locks gap before rec insert intention waiting
    Record lock, heap no 290 PHYSICAL RECORD: n_fields 2; compact format; info bits 0
     0: len 30; hex 313430333939383136313736323536313637383335343338383736363239; asc 140399816176256167835438876629; (total 32 bytes);
     1: len 8; hex 80000000000046a9; asc       F ;;
    
    *** WE ROLL BACK TRANSACTION (2)
    ------------
    TRANSACTIONS
    
    ```

    

  - deadlock analysis

    - reference document

      https://bugs.mysql.com/bug.php?id=21356

    - 

- 索引优化案例

  - 统计条数的优化
  - 查询没有命中索引的优化

