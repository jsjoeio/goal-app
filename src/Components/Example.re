open ApolloHooks;

module GetExchangeRates = [%graphql
  {|
  query getExchangeRates {
    rates(currency: "USD") {
      currency
      rate
    }
  }
|}
];

[@react.component]
let make = () => {
  let (simple, _full) = useQuery(GetExchangeRates.definition);

  <div>
    {switch (simple) {
     | Loading => <p> {React.string("Loading...")} </p>
     | Data(data) =>
       //  let thingDivs =
       //    Array.map(thing => <div> {React.string(thing)} </div>, things);
       //  React.array(thingDivs);
       let currencies =
         switch (data##rates) {
         | Some(rates) =>
           // do something
           Array.map(
             rate =>
               switch (rate) {
               | Some(rate) =>
                 switch (rate##currency) {
                 | Some(currency) => <p> {React.string(currency)} </p>
                 | None => React.null
                 }
               | None => React.null
               },
             rates,
           )
         | None => [|React.null|]
         };
       React.array(currencies);
     //  let currencies = switch(data##rates) {
     //    | Some(rates) => // 1
     //      // 2:
     //      Belt.Array.map(rates, item =>
     //        // 3:
     //        switch(item) {
     //          // If we have the item, we can then go to the first value which is currency
     //        | Some(rate) =>
     //          switch(rate##currency) {
     //            | Some (currency) =>
     //              <p>{React.string(currency)}</p>
     //            | None => React.null
     //          }
     //        | None => React.null
     //        }
     //    | None => React.null
     //  };
     | NoData
     | Error(_) => <p> {React.string("Get off my lawn!")} </p>
     }}
  </div>;
} /* 4. access the object propert*/ /* 2. map over the arra*/ /* 3. unwrap each option typ*/ /* 1. unwrap the optio*/;