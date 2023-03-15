### SOFTWARE-DESIGN-PATTERN

1. #### Software design principles and pattern (SOLID)

   - Single responsibility principle (SRP)

     - The best structure for a software system heavily influenced by the social structure of the organization that use it so that uses it so that software module have one, and only one, reason to change .

   - Open-closed principle (OCP)

     - The gist is that for software system is easy to change ,they must be designed to allow the behavior of thoes systems to be changed by adding new code ,rather than changing existing code .

   - Liskov substtitution principles (LSP)

     - In short ,this principle says that to build software systems from inerchanable parts .

     - What is wanted here is something like the following substutution property : If for each object o1 of type S there is an Object o2 of type T such that for all programs P defined in terms of T ,the behavior of P is unchanged when o1 substituted for o2 then S is a subtype of T.

       - Guiding the use of inheritance

          

       - LSP and architecture

     - 

   - Interface segregation principle(ISP)

   - Dependency inversion principle (DIP)

     - High-level modules should not depend on low-level modules .Both should  depend on abstractions.

       It is natural for us to write code folloing the structured programing :

       ```java
       class CriticalFeature {  
           private Step1 step1;  
           private Step2 step2;  ...    
               void run() {    
               // 执行第一步    step1.execute();   
               // 执行第二步    step2.execute();   
               ...  }
       }
       // The high level modules should depend on the low level modules.
       ```

       The called Dependency inversion is to reverse this habitual practice ,so that the high level modules should not depend on low level modules .

       All problem in computer science can be solved by another level of indirection .

       ```java
       interface MessageSender { 
           void send(Message message);
       }
       class Handler { 
           private MessageSender sender; 
           void execute() { 
               ... Message message = ...; 
               sender.send(message); ... 
           }
       }
       
       class KafkaMessageSender implements MessageSender { 
           private KafkaProducer producer; 
           public void send(final Message message) { 
               this.producer.send(new KafkaRecord<>("topic", message)); 
           }
       }
       ```

     - Abstractions should not depend on details .Details (concrete  implementations) should depend on abstractions.

       1.  No variable should be an instance of a concrete class .
       2. No  class should be an sub-class of a concrete class .
       3. No method should ovveride a method already implemented in parent class .

       If your common language does't provide a DI container ,It's better to put he code responsibility fo assembly and business model in different code .

       It's important to undertant dependency relationship between different modules  for a project .

       Anti-Corruption Layer ? do you understand?

2. #### Architechture principle

   1. #### Component Coupling 

      1. ##### SDP(Stable Dependence Principle)

      2. ##### ADP(Acyclic Dependecnies Principle)
   
      3. ##### SAP(The Stable Abstractions Princiole)
   
         - The stable abstractions Principle sets up a replationship 
   
      4. 
   
   2. #### Component Cohesion 
   
      1. ##### REP(The Reuse/Release Equibalence Principle)
   
      2. ##### CCP(The common Closeure Principle)
   
         - This is Single Repoinsibility Principle restated for components .
         - 
   
      3. ##### CRP(The common Reuse Principle)
   
3. #### Refactoring  - Improving the design of existing code .

   1. ##### Extract Method 

      - ###### Temporary variables can be problem . Replacte temporary variables with query method .

        ```java
        class Customer...
        public String statement() {
        double totalAmount = 0;
        int frequentRenterPoints = 0;
        Enumeration rentals = _rentals.elements();
        String result = "Rental Record for " + getName() + "\n";
        while (rentals.hasMoreElements()) {
        Rental each = (Rental) rentals.nextElement();
        frequentRenterPoints += each.getFrequentRenterPoints();
        //show figures for this rental
        result += "\t" + each.getMovie().getTitle()+ "\t" +
        String.valueOf(each.getCharge()) + "\n";
        totalAmount += each.getCharge();
        }
        //add footer lines
        result += "Amount owed is " + String.valueOf(totalAmount) +
        "\n";
        result += "You earned " + String.valueOf(frequentRenterPoints)
        +
        " frequent renter points";
        return result;
        }
        ```

        

      - ###### It is a bad idea to do a switch based on an attribute of another object

        - Replace Conditional with Polymorphism 

          We can use replace conditional with polymorphism with state pattern .The main idea of State pattern is to allow the object for changing tis behavior without changing its class .Also by implementing it ,the code should remain cleaner without many if/else statements.

   2. #### Principles in Refactoring 

      1. ##### Defining Refactoring 

         A change made to the internal structure of software to make it easier to understand and cheaper to modify withou chaning its observable behavior.

      2. 

   3. #### Bad Smells in Code

      1. #####  Duplicated Code 

         - You have the same exepression in two subclasses .    you can eliminate this duplication by using Extract Method in both classes then Pull  Up Field .
         - You see the same code structure in more than one place . 

      2. ##### Long Method 

         - More percent of the time ,All you have to do to shorten a method is **Extract Method** .
         - If you have a method with lots of parameters and temporary variables ,you can use **Extract Method** and **Replace Temp with Query** to elimate the temps . Long lists of parameters can be slilmmed down with Introduce **Parameter Object and Preserve Whole Object** 
         - If you've tried that ,and you still have too many temps and parameters ,it's time toe get out the heavy artillery : **Replace Method with Method Object .** 
         - Condition and loops alse give signs fro extractions . Use **Decompose Conditional** to deal with condition expression .With loops ,extract the loop and the code within the loop into its own method .

      3. 

   4. #### Building Tests

      1. Make sure all tests are fully automatic and that they check their own results .
      2. A suite of test is a powerful bug detector that decapitates the time it takes to find bugs .
      3. Run yout test frequetly .Localize tests whenever you compile - every test at least every day .
         1. 

      

4. ### DDD(Model -Driven Design)

   1. Event Storming(事件风暴)
      1. Three main event
         1. Identify domain event.
         2. Identify the action which lead to domain event command.
         3. Confirm the event and command related entities and aggregation.

   2. Model driven-design
      1. Strategic design 
         1. What' the problem and how to solve the problem
         2. subdomain ,core-domain ,support-domain,normal-domain
         3. Bounded context(限界上线文)
            1. Different object have different means in different context , such as  "Order" in transacton context is different that in transfer context.
            2. Every Bounded context should be a microservice. Most import for bounded context  is that  you should not enter other system to do some huge business logic  to complete the business require in yourself bounded context.
            3. Context map(上下文映射图)
               1. Context map aim to decrip  the detail of interaction among different bounded context.
                  1. Partnership (合作关系)
                  2. Shared Kernel(共享内核)
                  3. Customer - Supplier (客户-供应商)
                  4. Conformist (跟随着)
                  5. Anticorruption layer(防腐层) --- most import 
                  6. Open Host Service(开放主机服务)
                  7. Published languagre(发布语言)
                  8. Separate ways (各行其道)
                  9. Big Ball of Mud (大泥球)  -- most possible to avoid the interaction method.

      2. Tactical Design
         1. Role : Entity and V

​				State machine 

