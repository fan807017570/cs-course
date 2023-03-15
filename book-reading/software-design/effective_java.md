## EFFECTIVE  JAVA 



- Chapter1 -- Creating and Destroying Objects .

  - Use static factory method instead of constructor  . 

    - mertis of static factory 

      1. Static factory method can have different names but constructor.
      2. Static factory are not reqiried create a new object each time they're invoked.
      3. Static factory can return an object of any subtype of their return type 
      4. Static factory can vary from call to call as input parameters 

    - Common names for staic factory :

      1. from 

      2. of 

      3. valueOf

      4. instance / getInstance

      5. create /newInstance

      6. getType 

      7. newType

         Files.newBufferReader();

      8. type

         Collections.list()

- Class and interface 

  - Minimize the accessibility of classes and members 

    - make each class or member as inaccessible as possible.
    - There are for possible access levels  for members 
      1. privte
         - The member is accessible only from the top-level class where it is declared 
      2. package-private 
         - The member is accessible from any class in the package where it is declared .
      3. protected
         - The member is accessible from subclass of the class where it is declared.
      4. public
         - everywhere .

  - Instance fields of public classes should rarely be public.

  - A nonzero-length array is always mutable ,so it is wrong for a class to have a public static final array field ,or an accessor that returns such a field.

    1.  potential security hole 

       ```java
       public static final Thing[] VALUES = { ... };  // the Thing reference the array ,the modifies of Thing is public ,so maybe modified by others .may cause disauster result.
       ```

       fixe code :

       ```java
       private static final Thing[] PRIVATE_VALUES = { ... };
       public static final Thing[] values() {
       return PRIVATE_VALUES.clone();
       }
       
       
       private static final Thing[] PRIVATE_VALUES ={};
       public static final List<Thing> VALUES = Collections.unmodifiableList(Arrays.asList(PRIVATE_VALUES))
       ```

       

    2. 

- other .function program 

  - Some interface   provide for function program 

    - Optional<T> 

      1. NullPointerException created by Tony Hoare in 1965 . (NullPointerExceptoin is easy to implement but is a gad practice )

         code list1:

         ```java
         String version = computer.getSoundcard().getUSB().getVersion(); // for get the version of the usb ,but there are many computer have no use . So the client may get NullPointerException .
         ```

         code list2 : how to elimate NullPointerException :

         ```java 
         // Code becomes so ugly due to nested check.
         String version = "UNKNOWN";
         if(computer != null){
           Soundcard soundcard = computer.getSoundcard();
           if(soundcard != null){
             USB usb = soundcard.getUSB();
             if(usb != null){
               version = usb.getVersion();
             }
           }
         }
         ```

         

      2. Default  Values and Actions 

         ```java
         maybeSoundCard.orElse(new Sounder("default"))
         maybeSoundCard.orElseThrow(IllegalStateException::new) 
         ```

      3. Rejecting Certain Values Using  the filter Method

         ```java
         Optional<USB> maybeUSB = ...;
         maybeUSB.filter(usb->"3.0".equals(usb.getVersion())).ifPresent(()->System.out.println("ok"));
         
         ```

          

      4. Exracting and Transforming Values Using the map Method\

      4. Hide Delegate 
    
      4. 

         ```java
         maybeSoundCard.map(SoundCard::getUSB).filter(usg->"3.0".equals(usb.getVersion())).ifPresent(()->System.out.println("ok"));
         ```

         
    
         1. Cascading Optional Objects Using the flatMap Method .
    
         ```java
         String version = computer.flatMap(Computer::getSoundcard)
                            .flatMap(Soundcard::getUSB)
                            .map(USB::getVersion)
                            .orElse("UNKNOWN");
         ```

         

    - Predicate<T> 
    
    - Lambda expressions usage 
    
      1. High order functions .
      2. Returning a function 
      3. First - class function 
      4. The pure function 
      5. Support repreated execution .
      6. Eliminating dependencies between functions .
      7. Support lazy evaluation .
    
    - Functional programming concepts in Java .

- 

- model ， interface , implement details .

- Function curation (函数柯理化)

- #### Refactoring  - imporving the design of existing code

  - ##### Some  refactoring principle 

    - Hide Delegate 

    - Remove Middle Man
      A class is doing too much simple delegation. Get the client to call the delegate directly.

    - Introduce Foreign Method

      A server class you are using needs an additional method ,but you don't modify the  class . Create a method in the client class with an instance of server class as its first parameter.

    - Introduce Local extenson

      A server class you are using needs several additional methods .but you can't modify the class  ,Create a new class that contains these extra methods. Make this extension class a subclass or a wrapper of the original.

- #### Refactoring to Patterns 

  - ##### Replace Mutiple Constructors with Creation Methods

    Many constructors on a class make it hard to decide which constructors to call during development .

    Replace the constructors with intension-revealing Creation Methods that return Ob

  - fda 

